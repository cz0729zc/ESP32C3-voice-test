/**
 * @file app_init.c
 * @brief Application and board level initializations.
 *
 * This file implements functions related to the initialization of various
 * hardware peripherals and software services used in the application.
 */

#include "esp_log.h"
#include "esp_spiffs.h"
#include "app_init.h"
#include <dirent.h>
#include <sys/stat.h>

static const char *TAG = "app_init";

/**
 * @brief Initializes the SPIFFS filesystem.
 */
esp_err_t app_spiffs_init(void)
{
    ESP_LOGI(TAG, "Initializing SPIFFS");

    esp_vfs_spiffs_conf_t conf = {
      .base_path = "/spiffs",
      .partition_label = "storage",
      .max_files = 5,
      .format_if_mount_failed = false
    };

    // Register SPIFFS filesystem
    esp_err_t ret = esp_vfs_spiffs_register(&conf);

    if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            ESP_LOGE(TAG, "Failed to mount or format filesystem");
        } else if (ret == ESP_ERR_NOT_FOUND) {
            ESP_LOGE(TAG, "Failed to find SPIFFS partition");
        } else {
            ESP_LOGE(TAG, "Failed to initialize SPIFFS (%s)", esp_err_to_name(ret));
        }
        return ret;
    }

    // Get and print partition info
    size_t total = 0, used = 0;
    ret = esp_spiffs_info(conf.partition_label, &total, &used);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to get SPIFFS partition information (%s)", esp_err_to_name(ret));
    } else {
        ESP_LOGI(TAG, "Partition size: total: %d, used: %d", total, used);
        // Enumerate files under /spiffs for debugging
        DIR *dir = opendir(conf.base_path);
        if (dir == NULL) {
            ESP_LOGW(TAG, "opendir(%s) failed", conf.base_path);
        } else {
            struct dirent *entry;
            ESP_LOGI(TAG, "Listing files under %s:", conf.base_path);
            while ((entry = readdir(dir)) != NULL) {
                char path[512];
                int written = snprintf(path, sizeof(path), "%s/%s", conf.base_path, entry->d_name);
                if (written < 0 || written >= (int)sizeof(path)) {
                    ESP_LOGW(TAG, "  path too long, skip: base=%s name=%s", conf.base_path, entry->d_name);
                    continue;
                }
                struct stat st;
                if (stat(path, &st) == 0) {
                    ESP_LOGI(TAG, "  %s  size=%ld", path, (long)st.st_size);
                } else {
                    ESP_LOGI(TAG, "  %s  (stat failed)", path);
                }
            }
            closedir(dir);
        }
    }
    return ESP_OK;
}