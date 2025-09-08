#include "bsp_lcd.h"
#include "bsp_lvgl.h"
#include "app_events.h"
#include "app_motion.h"
#include "app_ui.h"

void app_main(void)
{
    /* BSP层初始化 */
    ESP_ERROR_CHECK(app_lcd_init());            // 初始化 LCD
    ESP_ERROR_CHECK(app_lvgl_init());           // 初始化 LVGL

    /* App层初始化 */
    app_events_init(); // 初始化应用事件模块
    app_motion_init(); // 初始化动作逻辑模块
    app_ui_init();     // 初始化UI模块
}