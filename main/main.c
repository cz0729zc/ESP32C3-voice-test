#include "bsp_lcd.h"
#include "bsp_lvgl.h"
#include "app_events.h"
#include "app_motion.h"
#include "app_ui.h"
#include "app_init.h"
#include "audio_player.h"
#include "esp_log.h"

void app_main(void)
{
    /* BSP层初始化 */
    ESP_ERROR_CHECK(app_lcd_init());            // 初始化 LCD
    ESP_ERROR_CHECK(app_lvgl_init());           // 初始化 LVGL
    ESP_ERROR_CHECK(app_spiffs_init());         // 初始化 SPIF
    ESP_ERROR_CHECK(audio_player_init(44100, 15));  // 初始化音频播放器

    /* App层初始化 */
    app_events_init(); // 初始化应用事件模块
    app_motion_init(); // 初始化动作逻辑模块
    app_ui_init();     // 初始化UI模块

    ESP_LOGI("main", "Playing sound.wav from SPIFFS...");
    audio_player_set_volume(100); // 设置为30%
    audio_player_play_wav("/spiffs/y848.wav");
}