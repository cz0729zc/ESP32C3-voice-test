#include "app_ui.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "app_events.h"
#include "lvgl.h"

static const char *TAG = "app_ui";

// 用于显示当前动作状态的标签
static lv_obj_t *status_label;

/**
 * @brief UI处理任务
 * @details
 *   此任务循环等待来自 app_logic 的动作事件,
 *   并根据事件更新UI。
 */
static void app_ui_task(void *pvParameters)
{
    ESP_LOGI(TAG, "UI 任务已启动");

    while (1) {
        // 等待任何一个动作事件的发生
        EventBits_t bits = xEventGroupWaitBits(
            g_action_event_group,
            ACTION_EVENT_BIT_STRAIGHT | ACTION_EVENT_BIT_LEFT | ACTION_EVENT_BIT_RIGHT | ACTION_EVENT_BIT_ACCELERATE,
            pdTRUE,  // 退出时清除事件位
            pdFALSE, // 不等待所有位置位，任何一个即可
            portMAX_DELAY);

        // 根据接收到的事件更新UI
        if ((bits & ACTION_EVENT_BIT_STRAIGHT) != 0) {
            lv_label_set_text(status_label, "state: stright");
            ESP_LOGI(TAG, "UI 更新: 直行");
        }
        if ((bits & ACTION_EVENT_BIT_LEFT) != 0) {
            lv_label_set_text(status_label, "state: Left");
            ESP_LOGI(TAG, "UI 更新: 左转");
        }
        if ((bits & ACTION_EVENT_BIT_RIGHT) != 0) {
            lv_label_set_text(status_label, "state: right");
            ESP_LOGI(TAG, "UI 更新: 右转");
        }
        if ((bits & ACTION_EVENT_BIT_ACCELERATE) != 0) {
            // 对于脉冲事件，可以显示一个临时动画或标签
            // 这里我们只在日志中打印
            lv_label_set_text(status_label, "state: su!!!!");
            ESP_LOGI(TAG, "UI 事件: 加速");
        }
    }
}

/**
 * @brief 初始化UI应用
 */
esp_err_t app_ui_init(void)
{
    ESP_LOGI(TAG, "UI 应用初始化");

    // 创建一个LVGL标签作为状态显示的占位符
    lv_obj_t *scr = lv_scr_act();
    status_label = lv_label_create(scr);
    lv_label_set_text(status_label, "state: init...");
    lv_obj_center(status_label);

    // 创建UI处理任务
    xTaskCreate(app_ui_task, "ui_task", 4096, NULL, 5, NULL);

    return ESP_OK;
}