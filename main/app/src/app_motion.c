#include "app_motion.h"
#include "service_imu.h"
#include "esp_log.h"
#include "app_events.h"

static const char *TAG = "app_motion"; // 日志标签

// 动作识别状态定义
typedef enum {
    ACTION_STATE_STRAIGHT, // 直行
    ACTION_STATE_TURN_LEFT,  // 左转
    ACTION_STATE_TURN_RIGHT, // 右转
} action_state_t;

// 用于状态机和阈值判断的宏定义
#define TURN_START_THRESHOLD    30.0f // 进入“转向”状态的角度阈值
#define TURN_STOP_THRESHOLD     15.0f // 从“转向”返回“直行”状态的角度阈值
#define ACCELERATE_THRESHOLD_G  1.2f  // 判定为“加速”的Z轴加速度阈值 (单位: g)

// 保存当前动作状态的静态变量
static action_state_t s_current_action_state = ACTION_STATE_STRAIGHT;

/**
 * @brief IMU 数据回调函数
 * @details
 *   此函数由 service_imu 层在计算出新的IMU数据后调用。
 *   这里将实现应用的业务逻辑：根据姿态和加速度数据进行动作识别。
 *
 * @param data 包含姿态角和Z轴加速度的IMU数据结构体
 */
static void imu_data_cb(imu_data_t data)
{
    action_state_t last_state = s_current_action_state;

    // 状态机逻辑
    switch (s_current_action_state) {
        case ACTION_STATE_STRAIGHT:
            if (data.angle.roll > TURN_START_THRESHOLD) {
                s_current_action_state = ACTION_STATE_TURN_RIGHT;
            } else if (data.angle.roll < -TURN_START_THRESHOLD) {
                s_current_action_state = ACTION_STATE_TURN_LEFT;
            }
            break;

        case ACTION_STATE_TURN_LEFT:
            if (data.angle.roll > -TURN_STOP_THRESHOLD) {
                s_current_action_state = ACTION_STATE_STRAIGHT;
            }
            break;

        case ACTION_STATE_TURN_RIGHT:
            if (data.angle.roll < TURN_STOP_THRESHOLD) {
                s_current_action_state = ACTION_STATE_STRAIGHT;
            }
            break;
    }

    // 如果状态发生变化，则发送事件通知UI层
    if (last_state != s_current_action_state) {
        switch (s_current_action_state) {
            case ACTION_STATE_STRAIGHT:
                xEventGroupSetBits(g_action_event_group, ACTION_EVENT_BIT_STRAIGHT);
                break;
            case ACTION_STATE_TURN_LEFT:
                xEventGroupSetBits(g_action_event_group, ACTION_EVENT_BIT_LEFT);
                break;
            case ACTION_STATE_TURN_RIGHT:
                xEventGroupSetBits(g_action_event_group, ACTION_EVENT_BIT_RIGHT);
                break;
        }
    }

    // 加速检测是独立的，不影响转向状态
    if (data.acce_z > ACCELERATE_THRESHOLD_G) {
        xEventGroupSetBits(g_action_event_group, ACTION_EVENT_BIT_ACCELERATE);
    }
}

/**
 * @brief 初始化动作识别应用
 * @details
 *   这是动作识别相关应用逻辑的入口。
 *   它负责初始化底层的服务，并设置好数据回调。
 *
 * @return esp_err_t 错误码
 */
esp_err_t app_motion_init(void)
{
    ESP_LOGI(TAG, "动作识别应用初始化");

    // 初始化IMU服务层
    esp_err_t ret = service_imu_init();
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "IMU 服务初始化失败");
        return ret;
    }

    // 注册回调函数，以便在获取到新数据时被调用
    service_imu_register_callback(imu_data_cb);

    // 启动IMU服务，开始后台数据采集和处理
    ret = service_imu_start();
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "IMU 服务启动失败");
        return ret;
    }

    ESP_LOGI(TAG, "动作识别应用启动成功");

    // 发送一个初始状态事件，确保UI有正确的初始状态
    xEventGroupSetBits(g_action_event_group, ACTION_EVENT_BIT_STRAIGHT);

    return ESP_OK;
}