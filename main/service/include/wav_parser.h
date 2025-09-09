/**
 * @file wav_parser.h
 * @brief A simple WAV file parser.
 * @version 0.1
 * @date 2025-08-12
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef WAV_PARSER_H
#define WAV_PARSER_H

#include <stdint.h>
#include <stdio.h>
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief WAV file header structure
 */
typedef struct {
    // RIFF Header
    char riff_header[4]; // Contains "RIFF"
    uint32_t wav_size; // Size of the WAV file
    char wave_header[4]; // Contains "WAVE"

    // Format Header
    char fmt_header[4]; // Contains "fmt "
    uint32_t fmt_chunk_size; // Should be 16 for PCM
    uint16_t audio_format; // Should be 1 for PCM
    uint16_t num_channels; // Number of channels
    uint32_t sample_rate; // Sample rate
    uint32_t byte_rate; // Bytes per second
    uint16_t sample_alignment; // 2 for 16-bit mono, 4 for 16-bit stereo
    uint16_t bit_depth; // Number of bits per sample

    // Data Header
    char data_header[4]; // Contains "data"
    uint32_t data_size; // Size of the data section
} wav_header_t;

/**
 * @brief Parses the WAV file header.
 *
 * @param fp Pointer to the file stream.
 * @param header Pointer to the wav_header_t structure to store the parsed data.
 * @return ESP_OK on success, ESP_FAIL on failure.
 */
esp_err_t wav_parser_parse_header(FILE *fp, wav_header_t *header);

#ifdef __cplusplus
}
#endif

#endif // WAV_PARSER_H