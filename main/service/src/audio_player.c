/**
 * @file audio_player.c
 * @brief 音频播放服务层实现
 * @version 0.1
 * @date 2025-08-01
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "audio_player.h"
#include "wav_parser.h"
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include "esp_log.h"
#include <stdatomic.h>

#ifdef CONFIG_AUDIO_PLAYER_ENABLE

#include "bsp_iis_MAX98357A.h"

static const char *TAG = "AUDIO_PLAYER";
#define WAV_BUFFER_SIZE 4096

// 软件音量（0-100），默认100%
static atomic_uint_fast8_t s_volume_percent = 100;

static inline int16_t audio_scale_sample(int16_t sample, uint8_t volume_percent)
{
    if (volume_percent >= 100) return sample;
    // 线性缩放，避免溢出，使用32位中间变量
    int32_t scaled = (int32_t)sample * (int32_t)volume_percent / 100;
    if (scaled > INT16_MAX) scaled = INT16_MAX;
    if (scaled < INT16_MIN) scaled = INT16_MIN;
    return (int16_t)scaled;
}

esp_err_t audio_player_set_volume(uint8_t percent)
{
    if (percent > 100) return ESP_ERR_INVALID_ARG;
    atomic_store(&s_volume_percent, percent);
    ESP_LOGI(TAG, "Set software volume: %u%%", percent);
    return ESP_OK;
}

esp_err_t audio_player_get_volume(uint8_t *percent)
{
    if (percent == NULL) return ESP_ERR_INVALID_ARG;
    *percent = atomic_load(&s_volume_percent);
    return ESP_OK;
}

/**
 * @brief 初始化音频播放服务
 */
esp_err_t audio_player_init(uint32_t sample_rate, uint8_t gain_db)
{
    ESP_LOGI(TAG, "Initializing audio player with sample rate: %lu, gain: %d dB", sample_rate, gain_db);
    esp_err_t ret = bsp_iis_max98357a_init(sample_rate);
    if (ret != ESP_OK) {
        return ret;
    }
    return bsp_iis_max98357a_set_gain(gain_db);
}

/**
 * @brief 播放原始PCM音频数据
 */
esp_err_t audio_player_play(const int16_t *data, size_t len)
{
    if (data == NULL || len == 0) {
        return ESP_ERR_INVALID_ARG;
    }

    // 读取当前音量
    uint8_t vol = atomic_load(&s_volume_percent);

    size_t bytes_written = 0;
    esp_err_t ret;
    if (vol >= 100) {
        // 直接写
        ret = bsp_iis_max98357a_write(data, len, &bytes_written, 1000);
    } else {
        // 音量缩放：在栈/堆上开辟临时缓冲并缩放
        // 注意：len 为字节数，必须为偶数
        size_t samples = len / sizeof(int16_t);
        // 为避免大栈占用，这里用堆缓冲
        int16_t *tmp = (int16_t *)malloc(len);
        if (tmp == NULL) {
            ESP_LOGE(TAG, "No memory for volume scaling buffer");
            return ESP_ERR_NO_MEM;
        }
        for (size_t i = 0; i < samples; i++) {
            tmp[i] = audio_scale_sample(data[i], vol);
        }
        ret = bsp_iis_max98357a_write(tmp, len, &bytes_written, 1000);
        free(tmp);
    }
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to write audio data, error: %d", ret);
    }
    if (bytes_written < len) {
        ESP_LOGW(TAG, "Not all bytes were written. Total: %d, Written: %d", len, bytes_written);
    }
    return ret;
}

/**
 * @brief 停止音频播放
 */
esp_err_t audio_player_stop(void)
{
    ESP_LOGI(TAG, "Stopping audio player");
    return bsp_iis_max98357a_stop();
}

/**
 * @brief 反初始化音频播放服务
 */
esp_err_t audio_player_deinit(void)
{
    ESP_LOGI(TAG, "Deinitializing audio player");
    return bsp_iis_max98357a_deinit();
}
/**
 * @brief 播放指定时长的音频
 */
esp_err_t audio_player_play_for(const int16_t *audio_data, size_t audio_data_len, uint32_t sample_rate, int duration_ms)
{
    if (audio_data == NULL || audio_data_len == 0 || sample_rate == 0 || duration_ms <= 0) {
        return ESP_ERR_INVALID_ARG;
    }

    // 计算单段音频数据的播放时长 (毫秒)
    // 由于数据是 int16_t (每个采样点2字节), 采样点数量为 audio_data_len / 2
    float single_play_duration_ms = ((float)audio_data_len / 2.0f / (float)sample_rate) * 1000.0f;

    if (single_play_duration_ms == 0) {
        return ESP_ERR_INVALID_ARG;
    }

    // 计算需要循环播放的次数
    int loop_count = (int)((float)duration_ms / single_play_duration_ms);
    if (loop_count == 0) {
        loop_count = 1; // 至少播放一次
    }

    ESP_LOGI(TAG, "开始播放音频，持续时间: %d ms，循环次数: %d", duration_ms, loop_count);

    // 循环播放音频数据
    for (int i = 0; i < loop_count; i++) {
        esp_err_t ret = audio_player_play(audio_data, audio_data_len);
        if (ret != ESP_OK) {
            // 如果写入失败, 立即停止并返回错误
            audio_player_stop();
            return ret;
        }
    }

    // 循环结束后停止播放
    return audio_player_stop();
}

esp_err_t audio_player_play_wav(const char *filepath)
{
    if (filepath == NULL) {
        ESP_LOGE(TAG, "Filepath is NULL");
        return ESP_ERR_INVALID_ARG;
    }

    struct stat st;
    if (stat(filepath, &st) != 0) {
        ESP_LOGE(TAG, "stat failed, file not found: %s", filepath);
    } else {
        ESP_LOGI(TAG, "File exists: %s, size=%ld", filepath, (long)st.st_size);
    }

    FILE *fp = fopen(filepath, "rb");
    if (fp == NULL) {
        ESP_LOGE(TAG, "Failed to open file: %s (errno=%d)", filepath, errno);
        return ESP_ERR_NOT_FOUND;
    }

    wav_header_t wav_header;
    if (wav_parser_parse_header(fp, &wav_header) != ESP_OK) {
        ESP_LOGE(TAG, "Failed to parse WAV header");
        fclose(fp);
        return ESP_FAIL;
    }

    // Re-initialize I2S with the sample rate from the WAV file
    audio_player_deinit();
    audio_player_init(wav_header.sample_rate, 15); // 默认15dB增益，音量用软件控制

    int16_t *buffer = malloc(WAV_BUFFER_SIZE);
    if (buffer == NULL) {
        ESP_LOGE(TAG, "Failed to allocate memory for WAV buffer");
        fclose(fp);
        return ESP_ERR_NO_MEM;
    }

    size_t bytes_read;
    do {
        bytes_read = fread(buffer, 1, WAV_BUFFER_SIZE, fp);

        if (bytes_read > 0) {
            // audio_player_play 内部会根据软件音量进行缩放
            audio_player_play(buffer, bytes_read);
        }
    } while (bytes_read > 0);

    free(buffer);
    fclose(fp);
    audio_player_stop();

    return ESP_OK;
}

#endif // CONFIG_AUDIO_PLAYER_ENABLE