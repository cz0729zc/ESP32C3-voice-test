#ifndef APP_UI_H_
#define APP_UI_H_

#include "esp_err.h"

/**
 * @brief 初始化UI应用
 * @details 这将创建UI任务，并初始化所有UI元素
 *
 * @return esp_err_t 错误码
 */
esp_err_t app_ui_init(void);

#endif /* APP_UI_H_ */