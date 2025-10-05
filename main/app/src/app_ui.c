#include "app_ui.h"
#include "esp_log.h"
#include "lvgl.h"
#include "app_lottie.h"


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

    // 创建一个状态标签，用于显示非动画状态（备用）
    status_label = lv_label_create(scr);
    lv_label_set_text(status_label, "state: init...");
    lv_obj_center(status_label);
    lv_obj_add_flag(status_label, LV_OBJ_FLAG_HIDDEN); // 默认隐藏

    // 默认播放 smile 动画
    // app_lottie_set_src(smile, 150, 150);
    // app_lottie_show(true);
    ESP_LOGI(TAG, "UI 初始化完成，默认播放 smile");

    return ESP_OK;
}

void app_ui_show_uniform_speed(int index)
{
    // 匀速/直行状态，播放 smile 动画
    // app_lottie_set_src(smile, 150, 150);
    // app_lottie_show(true);
    ESP_LOGI(TAG, "UI 更新: 匀速/直行 (smile Lottie)");
}

void app_ui_show_turn_left_start(void)
{
    // 左转开始，播放 danger 动画
    // app_lottie_set_src(danger, 150, 150);
    // app_lottie_show(true);
    ESP_LOGI(TAG, "UI 更新: 左转开始 (danger Lottie)");
}

void app_ui_show_turn_left_end(void)
{
    // 左转结束，播放 sad 作为过渡动画
    // app_lottie_set_src(sad, 150, 150);
    // app_lottie_show(true);
    ESP_LOGI(TAG, "UI 更新: 左转结束 (sad Lottie)");
}

void app_ui_show_turn_right_start(void)
{
    // 右转开始，播放 sad 动画
    // app_lottie_set_src(sad, 150, 150);
    // app_lottie_show(true);
    ESP_LOGI(TAG, "UI 更新: 右转开始 (sad Lottie)");
}

void app_ui_show_turn_right_end(void)
{
    // 右转结束，播放 danger 作为过渡动画
    // app_lottie_set_src(danger, 150, 150);
    // app_lottie_show(true);
    ESP_LOGI(TAG, "UI 更新: 右转结束 (danger Lottie)");
}

void app_ui_show_accelerate_start(void)
{
    // TODO: 实现加速开始的UI
    ESP_LOGI(TAG, "UI 更新: 加速开始 (未实现)");
}

void app_ui_show_accelerate_end(void)
{
    // TODO: 实现加速结束的UI
    ESP_LOGI(TAG, "UI 更新: 加速结束 (未实现)");
}

void app_ui_show_brake_start(void)
{
    // TODO: 实现刹车开始的UI
    ESP_LOGI(TAG, "UI 更新: 刹车开始 (未实现)");
}

void app_ui_show_brake_end(void)
{
    // TODO: 实现刹车结束的UI
    ESP_LOGI(TAG, "UI 更新: 刹车结束 (未实现)");
}

void app_ui_show_turn_left_hard(void)
{
    // 大力左转，同样播放 danger 动画
    // app_lottie_set_src(danger, 150, 150);
    app_lottie_show(true);
    ESP_LOGI(TAG, "UI 更新: 大力左转 (danger Lottie)");
}

void app_ui_show_turn_right_hard(void)
{
    // 大力右转，同样播放 sad 动画
    // app_lottie_set_src(sad, 150, 150);
    // app_lottie_show(true);
    ESP_LOGI(TAG, "UI 更新: 大力右转 (sad Lottie)");
}