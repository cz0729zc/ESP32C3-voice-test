#pragma once
#include "esp_err.h"
#include "esp_lcd_panel_ops.h"
#include "driver/gpio.h"

#define BSP_LCD_BL_ON_LEVEL     (1)

extern esp_lcd_panel_handle_t lcd_panel;

esp_err_t app_lcd_init(void);
void bsp_lcd_test(void);