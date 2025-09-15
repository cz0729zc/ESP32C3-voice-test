#include "bsp_lcd.h"
#include "bsp_lvgl.h"
#include "app_logic.h"
#include "app_init.h"
#include "audio_player.h"
#include "esp_log.h"

void app_main(void)
{
    /* BSP层初始化 */
    ESP_ERROR_CHECK(app_lcd_init());            // 初始化 LCD
    ESP_ERROR_CHECK(app_lvgl_init());           // 初始化 LVGL
    // ESP_ERROR_CHECK(app_spiffs_init());         // 初始化 SPIF
    // ESP_ERROR_CHECK(audio_player_init(44100, 15));  // 初始化音频播放器
    // ESP_ERROR_CHECK(audio_player_task_create(4096, 5)); // 创建音频播放任务

    /* App层初始化 */
    app_logic_init(); // 初始化应用核心逻辑

    // ESP_LOGI("main", "Playing sound.wav from SPIFFS...");
    // audio_player_set_volume(100); // 设置为30%
    // audio_player_play_wav("/spiffs/y848.wav");
}