/**
 * @file wav_parser.c
 * @brief 一个简单的WAV文件解析器实现。
 * @version 0.1
 * @date 2025-08-12
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "wav_parser.h"
#include "esp_log.h"
#include "esp_err.h"
#include <string.h>
static const char *TAG = "WAV_PARSER";

esp_err_t wav_parser_parse_header(FILE *fp, wav_header_t *header)
{
    if (fp == NULL || header == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    // 读取文件头
    size_t bytes_read = fread(header, 1, sizeof(wav_header_t), fp);
    if (bytes_read < sizeof(wav_header_t)) {
        ESP_LOGE(TAG, "读取WAV头部失败，读取了 %d 字节", bytes_read);
        return ESP_FAIL;
    }

    // 验证文件头
    if (strncmp(header->riff_header, "RIFF", 4) != 0 || strncmp(header->wave_header, "WAVE", 4) != 0) {
        ESP_LOGE(TAG, "无效的 RIFF/WAVE 头部");
        return ESP_FAIL;
    }

    if (header->audio_format != 1) {
        ESP_LOGE(TAG, "不支持的音频格式: %d。仅支持PCM。", header->audio_format);
        return ESP_FAIL;
    }
    
    ESP_LOGI(TAG, "WAV 文件格式:");
    ESP_LOGI(TAG, "  采样率: %lu", header->sample_rate);
    ESP_LOGI(TAG, "  位深度: %d", header->bit_depth);
    ESP_LOGI(TAG, "  通道数: %d", header->num_channels);
    ESP_LOGI(TAG, "  数据大小: %lu", header->data_size);


    return ESP_OK;
}