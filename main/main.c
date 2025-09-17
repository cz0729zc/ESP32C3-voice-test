#include "bsp_lcd.h"
#include "bsp_lvgl.h"
#include "app_logic.h"
#include "app_init.h"
#include "audio_player.h"
#include "esp_log.h"

#include "lvgl.h"
#include "esp_lvgl_port.h"
#include "maren.h"
#include "angry.h"
#include "smile.h"
#include "moneyface.h"

void app_main(void)
{
    /* BSP层初始化 */
    ESP_ERROR_CHECK(app_lcd_init());            // 初始化 LCD
    ESP_ERROR_CHECK(app_lvgl_init());           // 初始化 LVGL
    // ESP_ERROR_CHECK(app_spiffs_init());         // 初始化 SPIF
    // ESP_ERROR_CHECK(audio_player_init(44100, 15));  // 初始化音频播放器
    // ESP_ERROR_CHECK(audio_player_task_create(4096, 5)); // 创建音频播放任务

    /* App层初始化 */
    //app_logic_init(); // 初始化应用核心逻辑，它将负责UI的初始化

    lv_obj_t *scr = lv_scr_act();
 
    /* Task lock */
    lvgl_port_lock(0);

    // 检查可用内存
    size_t free_heap = esp_get_free_heap_size();
    ESP_LOGI("MAIN", "Free heap before Lottie: %zu bytes", free_heap);
    
    if (free_heap < 30000) { // 降低内存阈值
        ESP_LOGW("MAIN", "Memory low, showing simple label instead of Lottie");
        lv_obj_t *label = lv_label_create(scr);
        lv_label_set_text(label, "Memory Low");
        lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
    } else {
        lv_obj_set_style_bg_color(scr, lv_color_black(), 0);
        lv_obj_t *lottie = lv_rlottie_create_from_raw(scr, 150, 150, (const char *)maren);
        if (lottie != NULL) {
           lv_obj_center(lottie);
           ESP_LOGI("MAIN", "Complex Lottie animation created successfully");
        } else {
           ESP_LOGE("MAIN", "Failed to create complex Lottie animation");
           // 创建失败时显示简单文本
           lv_obj_t *label = lv_label_create(scr);
           lv_label_set_text(label, "Complex Lottie Failed");
           lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
        }
    }
    // 再次检查内存
    free_heap = esp_get_free_heap_size();
    ESP_LOGI("MAIN", "Free heap after display: %zu bytes", free_heap);

    lvgl_port_unlock();


}