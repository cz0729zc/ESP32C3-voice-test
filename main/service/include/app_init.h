/**
 * @file app_init.h
 * @brief Header for application and board level initializations.
 *
 * This file declares functions related to the initialization of various
 * hardware peripherals and software services used in the application.
 */

#ifndef APP_INIT_H
#define APP_INIT_H

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initializes the SPIFFS filesystem.
 *
 * This function configures and mounts the SPIFFS partition labeled "storage".
 * It sets up the base path to "/spiffs" and allows for a maximum of 5 open files.
 * If mounting fails, it will automatically format the partition.
 *
 * @return
 *      - ESP_OK on successful initialization.
 *      - ESP_FAIL if mounting or formatting fails.
 *      - ESP_ERR_NOT_FOUND if the specified SPIFFS partition is not found.
 *      - Other error codes from the underlying VFS/SPIFFS driver on other failures.
 */
esp_err_t app_spiffs_init(void);

#ifdef __cplusplus
}
#endif

#endif /* APP_INIT_H */