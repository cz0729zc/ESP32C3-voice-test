#include "app_imu.h"
#include "bsp_lcd.h"
#include "bsp_lvgl.h"

void app_main(void)
{
    ESP_ERROR_CHECK(app_lcd_init());            // 初始化 LCD
    ESP_ERROR_CHECK(app_lvgl_init());           // 初始化 LVGL
    bsp_lvgl_test_widgets();                    // LVGL 部件测试

    app_imu_init();
    //bsp_lcd_test();
}