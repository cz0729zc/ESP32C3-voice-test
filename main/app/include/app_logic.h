#ifndef APP_LOGIC_H_
#define APP_LOGIC_H_

#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "app_statemachine.h"

/**
 * @brief 初始化应用逻辑核心
 * @details
 *   - 初始化所有子模块 (UI, 运动检测等)
 *   - 创建并启动应用主逻辑任务
 *
 * @return esp_err_t 错误码
 */
esp_err_t app_logic_init(void);

/**
 * @brief 向应用逻辑层投递一个事件
 * @details
 *   这是一个线程安全的函数，可以从任何任务（如IMU中断处理）调用，
 *   将事件发送到 app_logic 的主任务进行处理。
 *
 * @param event 要投递的事件
 * @return BaseType_t pdTRUE 如果成功发送, pdFALSE 如果队列已满
 */
BaseType_t app_logic_post_event(app_event_t event);

#endif /* APP_LOGIC_H_ */