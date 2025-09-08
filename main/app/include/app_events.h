#ifndef APP_EVENTS_H_
#define APP_EVENTS_H_

#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"

// 全局事件组句柄，用于在不同模块间通信
extern EventGroupHandle_t g_action_event_group;

// 定义动作事件位
#define ACTION_EVENT_BIT_STRAIGHT   BIT(0) // 直行状态
#define ACTION_EVENT_BIT_LEFT       BIT(1) // 左转状态
#define ACTION_EVENT_BIT_RIGHT      BIT(2) // 右转状态
#define ACTION_EVENT_BIT_ACCELERATE BIT(3) // 加速脉冲事件

/**
 * @brief 初始化应用事件模块
 */
void app_events_init(void);

#endif /* APP_EVENTS_H_ */