#include "app_ui.h"
#include "esp_log.h"
#include "lvgl.h"
#include "app_lottie.h"
#include "Lottie/angry.h"

#include <stdio.h>

static const char *TAG = "app_ui";

// 用于显示当前状态的标签
static lv_obj_t *status_label;

esp_err_t app_ui_init(void)
{
    ESP_LOGI(TAG, "UI 应用初始化");

    lv_obj_t *scr = lv_scr_act();
    lv_obj_set_style_bg_color(scr, lv_color_black(), 0);
    // 初始化Lottie模块并创建动画
    app_lottie_init();
    app_lottie_create(scr);

    // 创建一个状态标签，用于显示非动画状态
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
    // 设置要播放的动画源并显示
    app_lottie_set_src(angry, 150, 150);
    lv_obj_add_flag(status_label, LV_OBJ_FLAG_HIDDEN); // 隐藏状态标签
    app_lottie_show(true);
    ESP_LOGI(TAG, "UI 更新: 左转开始 (angry Lottie)");
}

void app_ui_show_turn_left_end(void)
{
    // 隐藏Lottie动画
    app_lottie_show(false);
    lv_label_set_text(status_label, "Turn Left Finished");
    lv_obj_clear_flag(status_label, LV_OBJ_FLAG_HIDDEN); // 显示状态标签
    ESP_LOGI(TAG, "UI 更新: 左转结束");
}

void app_ui_show_turn_right_start(void)
{
    // TODO: 实现右转开始的UI
    app_lottie_set_src(angry, 150, 150);
    lv_obj_add_flag(status_label, LV_OBJ_FLAG_HIDDEN); // 隐藏状态标签
    app_lottie_show(true);
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

void app_ui_show_turn_left_hard(void)
{
    // TODO: 实现大力左转的“呼呼”UI
    lv_label_set_text(status_label, "Turning Left HARD!");
    ESP_LOGI(TAG, "UI 更新: 大力左转");
}

void app_ui_show_turn_right_hard(void)
{
    // TODO: 实现大力右转的UI
    lv_label_set_text(status_label, "Turning Right HARD!");
    ESP_LOGI(TAG, "UI 更新: 大力右转");
}