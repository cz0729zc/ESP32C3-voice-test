#ifndef APP_UI_H_
#define APP_UI_H_

#include "esp_err.h"

/**
 * @brief 初始化UI底层驱动和LVGL库
 * @note 这个函数不再创建任务，只做UI的底层准备工作。
 * @return esp_err_t 错误码
 */
esp_err_t app_ui_init(void);

// --- 匀速状态 UI ---
/**
 * @brief 显示第N个匀速状态的UI
 * @param index UI界面的索引 (0-9)
 */
void app_ui_show_uniform_speed(int index);

// --- 左转状态 UI ---
void app_ui_show_turn_left_start(void);
void app_ui_show_turn_left_end(void);

// --- 右转状态 UI (TODO) ---
void app_ui_show_turn_right_start(void);
void app_ui_show_turn_right_end(void);

// --- 加速状态 UI (TODO) ---
void app_ui_show_accelerate_start(void);
void app_ui_show_accelerate_end(void);

// --- 刹车状态 UI (TODO) ---
void app_ui_show_brake_start(void);
void app_ui_show_brake_end(void);

#endif /* APP_UI_H_ */