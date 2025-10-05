/**
 * @file audio_player.c
 * @brief 音频播放服务层实现
 * @version 0.2
 * @date 2025-09-10
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdatomic.h>
#include <string.h>
#include "audio_player.h"
#include "wav_parser.h"

#ifdef CONFIG_AUDIO_PLAYER_ENABLE

#include "bsp_iis_MAX98357A.h"

static const char *TAG = "AUDIO_PLAYER";
#define WAV_BUFFER_SIZE 4096
#define AUDIO_QUEUE_SIZE 5

// FreeRTOS components
static QueueHandle_t s_audio_queue = NULL;
static TaskHandle_t s_audio_task_handle = NULL;

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
    ESP_LOGI(TAG, "Initializing audio player with sample rate: %lu, gain: %d dB", (unsigned long)sample_rate, gain_db);
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
        ret = bsp_iis_max98357a_write(data, len, &bytes_written, portMAX_DELAY);
    } else {
        // 音量缩放
        size_t samples = len / sizeof(int16_t);
        int16_t *tmp = (int16_t *)malloc(len);
        if (tmp == NULL) {
            ESP_LOGE(TAG, "No memory for volume scaling buffer");
            return ESP_ERR_NO_MEM;
        }
        for (size_t i = 0; i < samples; i++) {
            tmp[i] = audio_scale_sample(data[i], vol);
        }
        ret = bsp_iis_max98357a_write(tmp, len, &bytes_written, portMAX_DELAY);
        free(tmp);
    }
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to write audio data, error: %d", ret);
    }
    if (bytes_written < len) {
        ESP_LOGW(TAG, "Not all bytes were written. Total: %d, Written: %d", (int)len, (int)bytes_written);
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
    if (s_audio_task_handle) {
        vTaskDelete(s_audio_task_handle);
        s_audio_task_handle = NULL;
    }
    if (s_audio_queue) {
        vQueueDelete(s_audio_queue);
        s_audio_queue = NULL;
    }
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

    float single_play_duration_ms = ((float)audio_data_len / 2.0f / (float)sample_rate) * 1000.0f;

    if (single_play_duration_ms == 0) {
        return ESP_ERR_INVALID_ARG;
    }

    int loop_count = (int)((float)duration_ms / single_play_duration_ms);
    if (loop_count == 0) {
        loop_count = 1;
    }

    ESP_LOGI(TAG, "开始播放音频，持续时间: %d ms，循环次数: %d", duration_ms, loop_count);

    for (int i = 0; i < loop_count; i++) {
        esp_err_t ret = audio_player_play(audio_data, audio_data_len);
        if (ret != ESP_OK) {
            audio_player_stop();
            return ret;
        }
    }

    return audio_player_stop();
}

static void _audio_player_task(void *pvParameters);

esp_err_t audio_player_task_create(uint32_t stack_depth, UBaseType_t priority)
{
    if (s_audio_queue == NULL) {
        s_audio_queue = xQueueCreate(AUDIO_QUEUE_SIZE, sizeof(char *));
        if (s_audio_queue == NULL) {
            ESP_LOGE(TAG, "Failed to create audio queue");
            return ESP_ERR_NO_MEM;
        }
    }

    if (s_audio_task_handle == NULL) {
        BaseType_t ret = xTaskCreate(_audio_player_task, "AudioPlayerTask", stack_depth, NULL, priority, &s_audio_task_handle);
        if (ret != pdPASS) {
            ESP_LOGE(TAG, "Failed to create audio task");
            return ESP_ERR_NO_MEM;
        }
    }
    return ESP_OK;
}

esp_err_t audio_player_play_wav(const char *filepath)
{
    if (filepath == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    if (s_audio_queue == NULL) {
        ESP_LOGE(TAG, "Audio task not initialized. Call audio_player_task_create first.");
        return ESP_ERR_INVALID_STATE;
    }

    char *filepath_copy = strdup(filepath);
    if (filepath_copy == NULL) {
        ESP_LOGE(TAG, "Failed to allocate memory for filepath");
        return ESP_ERR_NO_MEM;
    }

    if (xQueueSend(s_audio_queue, &filepath_copy, pdMS_TO_TICKS(100)) != pdPASS) {
        ESP_LOGW(TAG, "Failed to send to audio queue. Queue might be full.");
        free(filepath_copy);
        return ESP_FAIL;
    }

    return ESP_OK;
}

static void _audio_player_task(void *pvParameters)
{
    char *filepath = NULL;
    int16_t *buffer = malloc(WAV_BUFFER_SIZE);
    if (buffer == NULL) {
        ESP_LOGE(TAG, "Failed to allocate memory for WAV buffer in task, task aborting.");
        vTaskDelete(NULL);
        return;
    }

    ESP_LOGI(TAG, "Audio player task started.");

    for (;;) {
        if (xQueueReceive(s_audio_queue, &filepath, portMAX_DELAY) == pdPASS) {
            if (filepath == NULL) continue;

            ESP_LOGI(TAG, "Playing WAV from task: %s", filepath);

            struct stat st;
            if (stat(filepath, &st) != 0) {
                ESP_LOGE(TAG, "stat failed, file not found: %s", filepath);
                goto cleanup;
            }

            FILE *fp = fopen(filepath, "rb");
            if (fp == NULL) {
                ESP_LOGE(TAG, "Failed to open file: %s (errno=%d)", filepath, errno);
                goto cleanup;
            }

            wav_header_t wav_header;
            if (wav_parser_parse_header(fp, &wav_header) != ESP_OK) {
                ESP_LOGE(TAG, "Failed to parse WAV header");
                fclose(fp);
                goto cleanup;
            }

            (void)bsp_iis_max98357a_disable(); // Disable before reconfiguring, ignore error if already disabled
            if (bsp_iis_max98357a_reconfig_clk(wav_header.sample_rate) != ESP_OK) {
                ESP_LOGE(TAG, "Failed to reconfig I2S clock");
                fclose(fp);
                goto cleanup;
            }
            bsp_iis_max98357a_set_gain(15);
            bsp_iis_max98357a_enable(); // Enable before writing

            size_t bytes_read;
            do {
                bytes_read = fread(buffer, 1, WAV_BUFFER_SIZE, fp);
                if (bytes_read > 0) {
                    if (wav_header.num_channels == 2) {
                        // 立体声转单声道 (只取左声道)
                        size_t mono_samples = bytes_read / 4; // 2 channels, 2 bytes per sample
                        int16_t *mono_buffer = (int16_t *)malloc(mono_samples * sizeof(int16_t));
                        if (mono_buffer) {
                            for (size_t i = 0; i < mono_samples; i++) {
                                mono_buffer[i] = buffer[i * 2];
                            }
                            audio_player_play(mono_buffer, mono_samples * sizeof(int16_t));
                            free(mono_buffer);
                        }
                    } else {
                        // 单声道直接播放
                        audio_player_play(buffer, bytes_read);
                    }
                }
            } while (bytes_read > 0);

            (void)bsp_iis_max98357a_disable(); // Disable after playing, ignore error
            fclose(fp);
            ESP_LOGI(TAG, "Finished playing: %s", filepath);

        cleanup:
            free(filepath);
            filepath = NULL;
        }
    }

    free(buffer);
    vTaskDelete(NULL);
}

#endif // CONFIG_AUDIO_PLAYER_ENABLE