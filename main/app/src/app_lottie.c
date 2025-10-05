#include "app_lottie.h"
#include "esp_log.h"
#include "esp_lvgl_port.h"
#include "lvgl.h"
#include "libs/rlottie/lv_rlottie.h" // 包含我们添加了新函数的公共头文件

static const char *TAG = "app_lottie";

// 用于保存Lottie动画对象的静态指针
static lv_obj_t *lottie_anim = NULL;
static lv_obj_t *lottie_parent = NULL;

void app_lottie_init(void)
{
    ESP_LOGI(TAG, "Lottie 模块初始化");
    // 目前不需要做任何事，但保留以备将来扩展
}

void app_lottie_create(lv_obj_t *parent)
{
    if (parent == NULL) {
        ESP_LOGE(TAG, "创建 Lottie 失败：父对象不能为空");
        return;
    }
    if (lvgl_port_lock(0)) {
        lottie_parent = parent;
        ESP_LOGI(TAG, "Lottie 播放器已创建");
        lvgl_port_unlock();
    }
}

void app_lottie_set_src(const char *lottie_data, lv_coord_t width, lv_coord_t height)
{
    // if (lottie_parent == NULL) {
    //     ESP_LOGE(TAG, "设置 Lottie 源失败：播放器未创建");
    //     return;
    // }
    // if (lottie_data == NULL) {
    //     ESP_LOGE(TAG, "设置 Lottie 源失败：动画数据不能为空");
    //     return;
    // }

    // if (lvgl_port_lock(0)) {
    //     // 如果不存在动画对象，则创建一个
    //     if (lottie_anim == NULL) {
    //         ESP_LOGI(TAG, "首次创建 Lottie 动画对象...");
    //         lottie_anim = lv_rlottie_create_from_raw(lottie_parent, width, height, lottie_data);
    //         if (lottie_anim) {
    //             lv_obj_center(lottie_anim);
    //             lv_obj_add_flag(lottie_anim, LV_OBJ_FLAG_HIDDEN);
    //             ESP_LOGI(TAG, "Lottie 动画源设置成功");
    //         } else {
    //             ESP_LOGE(TAG, "从新数据创建 Lottie 动画失败");
    //         }
    //     } else { // 如果已存在，则调用新函数高效替换动画
    //         ESP_LOGI(TAG, "重用 Lottie 对象，正在设置新的动画源...");
    //         lv_rlottie_replace_raw(lottie_anim, lottie_data);
    //         ESP_LOGI(TAG, "Lottie 动画源更新成功");
    //     }
    //     lvgl_port_unlock();
    // }
}

void app_lottie_show(bool show)
{
    if (lottie_anim == NULL) {
        ESP_LOGW(TAG, "Lottie 对象不存在，无法显示/隐藏");
        return;
    }
    if (lvgl_port_lock(0)) {
        if (show) {
            lv_obj_clear_flag(lottie_anim, LV_OBJ_FLAG_HIDDEN);
            ESP_LOGI(TAG, "显示 Lottie 动画");
        } else {
            lv_obj_add_flag(lottie_anim, LV_OBJ_FLAG_HIDDEN);
            ESP_LOGI(TAG, "隐藏 Lottie 动画");
        }
        lvgl_port_unlock();
    }
}

void app_lottie_delete(void)
{
    if (lottie_anim) {
        if (lvgl_port_lock(0)) {
            lv_obj_del(lottie_anim);
            lottie_anim = NULL;
            ESP_LOGI(TAG, "Lottie 动画已删除");
            lvgl_port_unlock();
        }
    }
}