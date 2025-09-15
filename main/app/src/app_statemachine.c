#include "app_statemachine.h"
#include "app_logic.h"
#include "app_ui.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include <stdlib.h>

static const char *TAG = "app_sm";
static app_state_t current_state;
static TimerHandle_t uniform_speed_ui_timer;

static void uniform_speed_timer_callback(TimerHandle_t xTimer) {
    app_logic_post_event(APP_EVENT_TIMER_UNIFORM_UI);
}

// 状态进入动作处理
static void on_enter_state(app_state_t state) {
    ESP_LOGI(TAG, "进入状态: %d", state);
    switch (state) {
        case APP_STATE_UNIFORM_SPEED:
            // 进入匀速状态，显示一个随机的UI界面
            app_ui_show_uniform_speed(rand() % 10);
            // 启动一分钟定时器用于切换UI
            xTimerStart(uniform_speed_ui_timer, portMAX_DELAY);
            break;
        case APP_STATE_TURN_LEFT:
            // 进入左转状态，显示左转开始UI
            app_ui_show_turn_left_start();
            break;
       case APP_STATE_TURN_LEFT_HARD:
           app_ui_show_turn_left_hard();
           break;
        case APP_STATE_TURN_RIGHT:
            // 进入右转状态，显示右转开始UI
            app_ui_show_turn_right_start();
            break;
       case APP_STATE_TURN_RIGHT_HARD:
           app_ui_show_turn_right_hard();
           break;
        case APP_STATE_ACCELERATE:
            // 进入加速状态，显示加速开始UI
            app_ui_show_accelerate_start();
            break;
        case APP_STATE_BRAKE:
            // 进入刹车状态，显示刹车开始UI
            app_ui_show_brake_start();
            break;
        default:
            // 未知状态，不执行任何操作
            break;
    }
}

// 状态退出动作处理
static void on_exit_state(app_state_t state) {
    ESP_LOGI(TAG, "退出状态: %d", state);
    switch (state) {
        case APP_STATE_UNIFORM_SPEED:
            // 退出匀速状态，停止UI切换定时器
            xTimerStop(uniform_speed_ui_timer, portMAX_DELAY);
            break;
        case APP_STATE_TURN_LEFT:
        case APP_STATE_TURN_LEFT_HARD:
            // 退出左转状态，显示结束UI，并短暂延时
            app_ui_show_turn_left_end();
            vTaskDelay(pdMS_TO_TICKS(1000));
            break;
        case APP_STATE_TURN_RIGHT:
        case APP_STATE_TURN_RIGHT_HARD:
            // 退出右转状态，显示结束UI，并短暂延时
            app_ui_show_turn_right_end();
            vTaskDelay(pdMS_TO_TICKS(1000));
            break;
        case APP_STATE_ACCELERATE:
            // 退出加速状态，显示结束UI，并短暂延时
            app_ui_show_accelerate_end();
            vTaskDelay(pdMS_TO_TICKS(1000));
            break;
        case APP_STATE_BRAKE:
            // 退出刹车状态，显示结束UI，并短暂延时
            app_ui_show_brake_end();
            vTaskDelay(pdMS_TO_TICKS(1000));
            break;
        default:
            // 未知状态，不执行任何操作
            break;
    }
}

void app_statemachine_init(app_state_t initial_state) {
    // 创建一分钟周期的软件定时器，用于切换匀速状态下的UI
    uniform_speed_ui_timer = xTimerCreate(
        "uniform_ui_timer",         // 定时器名称
        pdMS_TO_TICKS(60 * 1000),   // 定时周期 (1分钟)
        pdTRUE,                     // 自动重载
        (void *)0,                  // 定时器ID
        uniform_speed_timer_callback // 回调函数
    );

    // 设置初始状态并执行进入动作
    current_state = initial_state;
    on_enter_state(current_state);
}

void app_statemachine_handle_event(app_event_t event) {
    app_state_t next_state = current_state;

    switch (current_state) {
        case APP_STATE_UNIFORM_SPEED:
            // 在匀速状态下，根据不同的动作事件切换到对应状态
            if (event == APP_EVENT_MOTION_TURN_LEFT_NORMAL) {
                next_state = APP_STATE_TURN_LEFT;
            } else if (event == APP_EVENT_MOTION_TURN_LEFT_HARD) {
               next_state = APP_STATE_TURN_LEFT_HARD;
            } else if (event == APP_EVENT_MOTION_TURN_RIGHT_NORMAL) {
                next_state = APP_STATE_TURN_RIGHT;
            } else if (event == APP_EVENT_MOTION_TURN_RIGHT_HARD) {
               next_state = APP_STATE_TURN_RIGHT_HARD;
            } else if (event == APP_EVENT_MOTION_ACCELERATE) {
                next_state = APP_STATE_ACCELERATE;
            } else if (event == APP_EVENT_MOTION_BRAKE) {
                next_state = APP_STATE_BRAKE;
            } else if (event == APP_EVENT_TIMER_UNIFORM_UI) {
                // 定时器事件触发，仅切换UI，不改变状态
                app_ui_show_uniform_speed(rand() % 10);
            }
            break;

        case APP_STATE_TURN_LEFT:
        case APP_STATE_TURN_LEFT_HARD:
        case APP_STATE_TURN_RIGHT:
        case APP_STATE_TURN_RIGHT_HARD:
        case APP_STATE_ACCELERATE:
        case APP_STATE_BRAKE:
            // 在任何一个动作状态下，接收到“动作结束”事件都会返回到匀速状态
            if (event == APP_EVENT_MOTION_ENDED) {
                next_state = APP_STATE_UNIFORM_SPEED;
            }
            break;

        default:
            // 未知状态，不处理事件
            break;
    }

    // 如果状态发生了迁移
    if (next_state != current_state) {
        on_exit_state(current_state);  // 执行当前状态的退出动作
        current_state = next_state;    // 更新状态
        on_enter_state(current_state); // 执行新状态的进入动作
    }
}