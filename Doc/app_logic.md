# 应用逻辑与状态机架构文档

本文档详细描述了应用的核心业务逻辑和状态机实现方案。

## 1. 核心思想

为了实现复杂的、带有时序的状态管理，我们将引入一个新的核心模块 `app_logic`。它将作为整个应用的“大脑”，负责：

-   管理应用的核心状态。
-   接收来自底层驱动（如 `app_motion`）的输入事件。
-   根据当前状态和输入事件，决策下一个状态。
-   向 `app_ui` 模块发出明确的、不带业务逻辑的渲染指令。

这种分层架构将业务逻辑与UI渲染彻底解耦，提高了代码的可维护性和可扩展性。

## 2. 状态转换图

```mermaid
stateDiagram-v2
    [*] --> UNIFORM_SPEED

    UNIFORM_SPEED: 匀速状态
    TURN_LEFT: 左转状态
    TURN_RIGHT: 右转状态
    ACCELERATE: 加速状态
    BRAKE: 刹车状态 (待实现)

    UNIFORM_SPEED --> TURN_LEFT: 检测到左转开始
    note on link
        1. 停止匀速UI切换定时器
        2. 显示左转开始UI
    end note
    TURN_LEFT --> UNIFORM_SPEED: 检测到动作结束
    note on link
        1. 显示左转结束UI
        2. (短暂延时后)
        3. 显示随机匀速UI
        4. 启动匀速UI切换定时器
    end note

    UNIFORM_SPEED --> TURN_RIGHT: 检测到右转开始
    TURN_RIGHT --> UNIFORM_SPEED: 检测到动作结束

    UNIFORM_SPEED --> ACCELERATE: 检测到加速开始
    ACCELERATE --> UNIFORM_SPEED: 检测到动作结束

    UNIFORM_SPEED --> BRAKE: 检测到刹车开始
    BRAKE --> UNIFORM_SPEED: 检测到动作结束

    UNIFORM_SPEED --> UNIFORM_SPEED: 1分钟定时器触发
    note on link
        切换到下一个随机UI
    end note
```

## 3. 文件创建与代码实现

在进入“Code”模式后，将根据以下规划创建和修改文件。

### 3.1. 新建文件：`main/app/include/app_statemachine.h`

该文件定义了状态机的核心数据结构：状态 (State) 和事件 (Event)。

```c
#ifndef APP_STATEMACHINE_H_
#define APP_STATEMACHINE_H_

#include "esp_err.h"

// 定义应用的所有可能状态
typedef enum {
    APP_STATE_UNIFORM_SPEED, // 匀速状态
    APP_STATE_TURN_LEFT,         // 普通左转状态
    APP_STATE_TURN_LEFT_HARD,    // 大力左转状态 (新)
    APP_STATE_TURN_RIGHT,        // 普通右转状态
    APP_STATE_TURN_RIGHT_HARD,   // 大力右转状态 (新)
    APP_STATE_ACCELERATE,    // 加速状态
    APP_STATE_BRAKE,         // 刹车状态 (TODO)
    APP_STATE_NUM_STATES     // 状态总数
} app_state_t;

// 定义驱动状态机迁移的事件
typedef enum {
    // --- 动作事件 ---
    APP_EVENT_MOTION_TURN_LEFT_NORMAL, // 动作：普通左转
    APP_EVENT_MOTION_TURN_LEFT_HARD,   // 动作：大力左转 (新)
    APP_EVENT_MOTION_TURN_RIGHT_NORMAL,// 动作：普通右转
    APP_EVENT_MOTION_TURN_RIGHT_HARD,  // 动作：大力右转 (新)
    APP_EVENT_MOTION_ACCELERATE,     // 动作：加速
    APP_EVENT_MOTION_BRAKE,          // 动作：刹车 (TODO)
    APP_EVENT_MOTION_ENDED,          // 动作：结束

    // --- 系统事件 ---
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
```

---
*下一步，我将继续在这份文档中添加 `app_statemachine.c`, `app_logic.h`, `app_logic.c` 的代码，并规划对 `app_ui.c/h` 的修改。*

### 3.2. 新建文件：`main/app/include/app_logic.h`

该文件定义了应用逻辑层的入口函数和事件投递接口。

```c
#ifndef APP_LOGIC_H_
#define APP_LOGIC_H_

#include "esp_err.h"
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
```

### 3.3. 新建文件：`main/app/src/app_logic.c`

这是应用的主循环，它等待事件，然后将其传递给状态机进行处理。

```c
#include "app_logic.h"
#include "app_ui.h"
#include "app_motion.h"
#include "app_statemachine.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"

static const char *TAG = "app_logic";

// 用于接收事件的FreeRTOS队列
static QueueHandle_t app_event_queue;

// 主逻辑任务
static void app_logic_task(void *pvParameters)
{
    ESP_LOGI(TAG, "应用逻辑任务已启动");

    // 初始化状态机，设定初始状态为“匀速”
    app_statemachine_init(APP_STATE_UNIFORM_SPEED);

    while (1) {
        app_event_t event;
        // 等待事件队列中的新事件
        if (xQueueReceive(app_event_queue, &event, portMAX_DELAY) == pdPASS) {
            ESP_LOGI(TAG, "接收到事件: %d", event);
            // 将事件交由状态机处理
            app_statemachine_handle_event(event);
        }
    }
}

esp_err_t app_logic_init(void)
{
    ESP_LOGI(TAG, "应用逻辑核心初始化");

    // 创建事件队列，用于任务间通信
    // TODO: 队列长度需要根据实际情况调整
    app_event_queue = xQueueCreate(10, sizeof(app_event_t));
    if (app_event_queue == NULL) {
        ESP_LOGE(TAG, "事件队列创建失败");
        return ESP_FAIL;
    }

    // TODO: 在这里初始化其他模块
    // app_motion_init();
    // app_ui_init();

    // 创建并启动主逻辑任务
    xTaskCreate(app_logic_task, "app_logic_task", 4096, NULL, 5, NULL);

    return ESP_OK;
}

BaseType_t app_logic_post_event(app_event_t event)
{
    // 线程安全地将事件发送到队列末尾
    return xQueueSend(app_event_queue, &event, 0);
}
```

### 3.4. 新建文件：`main/app/src/app_statemachine.c`

这是状态机的核心实现。它包含状态转换逻辑和与状态相关的动作（例如，启动/停止定时器，调用UI函数）。

```c
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

static void on_enter_state(app_state_t state) {
    ESP_LOGI(TAG, "进入状态: %d", state);
    switch (state) {
        case APP_STATE_UNIFORM_SPEED:
            app_ui_show_uniform_speed(rand() % 10);
            xTimerStart(uniform_speed_ui_timer, 0);
            break;
        case APP_STATE_TURN_LEFT:
            app_ui_show_turn_left_start();
            break;
        // ... 其他状态
    }
}

static void on_exit_state(app_state_t state) {
    ESP_LOGI(TAG, "退出状态: %d", state);
    switch (state) {
        case APP_STATE_UNIFORM_SPEED:
            xTimerStop(uniform_speed_ui_timer, 0);
            break;
        case APP_STATE_TURN_LEFT:
            app_ui_show_turn_left_end();
            vTaskDelay(pdMS_TO_TICKS(1000));
            break;
        // ... 其他状态
    }
}

void app_statemachine_init(app_state_t initial_state) {
    uniform_speed_ui_timer = xTimerCreate("uniform_timer", pdMS_TO_TICKS(60000), pdTRUE, 0, uniform_speed_timer_callback);
    current_state = initial_state;
    on_enter_state(current_state);
}

void app_statemachine_handle_event(app_event_t event) {
    app_state_t next_state = current_state;
    switch (current_state) {
        case APP_STATE_UNIFORM_SPEED:
            if (event == APP_EVENT_MOTION_TURN_LEFT) next_state = APP_STATE_TURN_LEFT;
            else if (event == APP_EVENT_TIMER_UNIFORM_UI) app_ui_show_uniform_speed(rand() % 10);
            break;
        case APP_STATE_TURN_LEFT:
            if (event == APP_EVENT_MOTION_ENDED) next_state = APP_STATE_UNIFORM_SPEED;
            break;
        // ... 其他状态
    }
    if (next_state != current_state) {
        on_exit_state(current_state);
        current_state = next_state;
        on_enter_state(current_state);
    }
}
```

## 4. 模块重构规划

### 4.1. 重构 `main/app/include/app_ui.h`

**目标**: 将 `app_ui.h` 改造成一个纯粹的、提供原子化UI显示功能的接口层。

**规划**:
-   修改 `app_ui_init` 的职责，只做底层初始化。
-   增加一系列新的函数声明，每个函数负责一个特定的UI场景。

**代码规划 (用于 `apply_diff`)**:
```c
// 在 app_ui.h 中增加以下函数声明
void app_ui_show_turn_left_hard(void); // 大力左转 (新)
void app_ui_show_turn_right_hard(void); // 大力右转 (新)
```

### 4.2. 重构 `main/app/src/app_ui.c`

**目标**: 移除内部的任务和事件逻辑，实现新的UI显示函数。

**规划**:
-   删除 `app_ui_task`。
-   修改 `app_ui_init`，移除 `xTaskCreate`。
-   实现所有 `app_ui_show_*` 函数，使用 `lv_label_set_text` 作为占位符。

**代码规划 (用于 `apply_diff`)**:
```c
// 在 app_ui.c 中增加以下函数实现

void app_ui_show_turn_left_hard(void)
{
    // TODO: 实现大力左转的“呼呼”UI
    lv_label_set_text(status_label, "Turning Left HARD!");
    ESP_LOGI(TAG, "UI 更新: 大力左转");
}

// ... 以及对应的右转版本
```

### 4.3. 动作识别升级 (`app_motion.c`)

**目标**: 升级动作识别逻辑，使其能根据角速度和角度区分不同的转向力度。

**前提**:
- `service_imu` 层需要提供角速度数据。我们需要扩展 `imu_data_t` 结构体，增加 `imu_vec_t gyro;` 成员。

**代码规划 (用于 `apply_diff`)**:

**1. 添加新阈值定义**
```c
// 在 app_motion.c 的宏定义区添加
#define TURN_HARD_GYRO_THRESHOLD  100.0f // 判定为“大力转向”的角速度阈值 (dps)
```

**2. 修改 `imu_data_cb` 状态机逻辑**
```c
// 重写 imu_data_cb 中的事件发送逻辑

// ... (状态迁移逻辑保持不变) ...

// --- 事件发送逻辑 (简化版) ---
if (last_state != s_current_action_state) {
    // 当状态刚从“直行”切换到“转向”时
    if (last_state == ACTION_STATE_STRAIGHT) {
        if (s_current_action_state == ACTION_STATE_TURN_LEFT) {
            // 检查进入左转时的角速度
            if (fabsf(data.gyro.y) > TURN_HARD_GYRO_THRESHOLD) {
                app_logic_post_event(APP_EVENT_MOTION_TURN_LEFT_HARD);
            } else {
                app_logic_post_event(APP_EVENT_MOTION_TURN_LEFT_NORMAL);
            }
        }
        // ... (对应的右转逻辑)
    }
    // 当状态从“转向”切换回“直行”时
    else if (s_current_action_state == ACTION_STATE_STRAIGHT) {
        app_logic_post_event(APP_EVENT_MOTION_ENDED);
    }
}
```

### 4.4. 状态机升级 (`app_statemachine.c`)

**目标**: 升级状态机，使其能够处理新的转向事件，并进入对应的新状态。

**代码规划 (用于 `apply_diff`)**:

**1. 修改 `on_enter_state` 函数**
```c
// 在 on_enter_state 的 switch 中增加 case
case APP_STATE_TURN_LEFT:
    app_ui_show_turn_left_start();
    break;
case APP_STATE_TURN_LEFT_HARD:
    app_ui_show_turn_left_hard();
    break;
// ... 对应的右转 case
```

**2. 修改 `on_exit_state` 函数**
```c
// 在 on_exit_state 的 switch 中，确保所有转向状态都能正确退出
case APP_STATE_TURN_LEFT:
case APP_STATE_TURN_LEFT_HARD:
    app_ui_show_turn_left_end();
    vTaskDelay(pdMS_TO_TICKS(1000)); // 短暂显示结束动画
    break;
// ... 对应的右转 case
```

**3. 修改 `app_statemachine_handle_event` 函数**
```c
// 重写 app_statemachine_handle_event 的状态处理逻辑
switch (current_state) {
    case APP_STATE_UNIFORM_SPEED:
        if (event == APP_EVENT_MOTION_TURN_LEFT_NORMAL) {
            next_state = APP_STATE_TURN_LEFT;
        } else if (event == APP_EVENT_MOTION_TURN_LEFT_HARD) {
            next_state = APP_STATE_TURN_LEFT_HARD;
        }
        // ... (对应的右转、加速、刹车逻辑)
        break;

    case APP_STATE_TURN_LEFT:
    case APP_STATE_TURN_LEFT_HARD:
        if (event == APP_EVENT_MOTION_ENDED) {
            next_state = APP_STATE_UNIFORM_SPEED;
        }
        break;

    // ... (对应的右转状态处理)
}
```

## 5. 系统集成

最后，修改应用主入口文件（如 `main.c`），将所有 `app_*_init()` 调用替换为单一的 `app_logic_init()` 调用。

---
*这份文档现在包含了所有必要的代码和设计规划。*