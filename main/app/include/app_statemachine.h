#ifndef APP_STATEMACHINE_H_
#define APP_STATEMACHINE_H_

#include "esp_err.h"

// 定义应用的所有可能状态
typedef enum {
    APP_STATE_UNIFORM_SPEED, // 匀速状态
    APP_STATE_TURN_LEFT,     // 左转状态
    APP_STATE_TURN_RIGHT,    // 右转状态
    APP_STATE_ACCELERATE,    // 加速状态
    APP_STATE_BRAKE,         // 刹车状态 (TODO)
    APP_STATE_NUM_STATES     // 状态总数
} app_state_t;

// 定义驱动状态机迁移的事件
typedef enum {
    APP_EVENT_MOTION_TURN_LEFT,      // 动作：左转
    APP_EVENT_MOTION_TURN_RIGHT,     // 动作：右转
    APP_EVENT_MOTION_ACCELERATE,     // 动作：加速
    APP_EVENT_MOTION_BRAKE,          // 动作：刹车 (TODO)
    APP_EVENT_MOTION_ENDED,          // 动作：结束
    APP_EVENT_TIMER_UNIFORM_UI,      // 定时器：匀速UI切换
    APP_EVENT_NUM_EVENTS             // 事件总数
} app_event_t;

/**
 * @brief 初始化状态机
 * @param initial_state 初始状态
 */
void app_statemachine_init(app_state_t initial_state);

/**
 * @brief 处理事件并执行状态迁移
 * @param event 触发的事件
 */
void app_statemachine_handle_event(app_event_t event);

/**
 * @brief 获取当前状态
 * @return app_state_t 当前状态
 */
app_state_t app_statemachine_get_current_state(void);

#endif /* APP_STATEMACHINE_H_ */