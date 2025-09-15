#include "app_ui.h"
#include "esp_log.h"
#include "lvgl.h"
#include <stdio.h>

static const char *TAG = "app_ui";

// 用于显示当前状态的标签
static lv_obj_t *status_label;

esp_err_t app_ui_init(void)
{
    ESP_LOGI(TAG, "UI 应用初始化");

    // 创建一个LVGL标签作为状态显示的占位符
    // 注意：这里不再创建任务
    lv_obj_t *scr = lv_scr_act();
    status_label = lv_label_create(scr);
    lv_label_set_text(status_label, "state: init...");
    lv_obj_center(status_label);

    return ESP_OK;
}

void app_ui_show_uniform_speed(int index)
{
    char buffer[32];
    // TODO: 在这里根据 index 显示 10 种不同的 UI 界面
    sprintf(buffer, "Uniform Speed UI: %d", index);
    lv_label_set_text(status_label, buffer);
    ESP_LOGI(TAG, "UI 更新: %s", buffer);
}

void app_ui_show_turn_left_start(void)
{
    // TODO: 实现左转开始的UI动画/界面
    lv_label_set_text(status_label, "Turning Left...");
    ESP_LOGI(TAG, "UI 更新: 左转开始");
}

void app_ui_show_turn_left_end(void)
{
    // TODO: 实现左转结束的UI动画/界面
    lv_label_set_text(status_label, "Turn Left Finished");
    ESP_LOGI(TAG, "UI 更新: 左转结束");
}

void app_ui_show_turn_right_start(void)
{
    // TODO: 实现右转开始的UI
    lv_label_set_text(status_label, "Turning Right...");
    ESP_LOGI(TAG, "UI 更新: 右转开始");
}

void app_ui_show_turn_right_end(void)
{
    // TODO: 实现右转结束的UI
    lv_label_set_text(status_label, "Turn Right Finished");
    ESP_LOGI(TAG, "UI 更新: 右转结束");
}

void app_ui_show_accelerate_start(void)
{
    // TODO: 实现加速开始的UI
    lv_label_set_text(status_label, "Accelerating...");
    ESP_LOGI(TAG, "UI 更新: 加速开始");
}

void app_ui_show_accelerate_end(void)
{
    // TODO: 实现加速结束的UI
    lv_label_set_text(status_label, "Accelerate Finished");
    ESP_LOGI(TAG, "UI 更新: 加速结束");
}

void app_ui_show_brake_start(void)
{
    // TODO: 实现刹车开始的UI
    lv_label_set_text(status_label, "Braking...");
    ESP_LOGI(TAG, "UI 更新: 刹车开始");
}

void app_ui_show_brake_end(void)
{
    // TODO: 实现刹车结束的UI
    lv_label_set_text(status_label, "Brake Finished");
    ESP_LOGI(TAG, "UI 更新: 刹车结束");
}