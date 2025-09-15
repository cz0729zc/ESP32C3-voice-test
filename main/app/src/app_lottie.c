#include "app_lottie.h"
#include "esp_log.h"

static const char *TAG = "app_lottie";

// 用于保存Lottie动画对象的静态指针
static lv_obj_t *lottie_anim = NULL;

void app_lottie_init(void)
{
    ESP_LOGI(TAG, "Lottie 模块初始化");
    // 目前不需要做任何事，但保留以备将来扩展
}

void app_lottie_create(lv_obj_t *parent, const char *lottie_data, lv_coord_t width, lv_coord_t height)
{
    if (lottie_anim != NULL) {
        ESP_LOGW(TAG, "Lottie 动画已存在，将先删除旧的");
        lv_obj_del(lottie_anim);
        lottie_anim = NULL;
    }

    if (parent == NULL || lottie_data == NULL) {
        ESP_LOGE(TAG, "创建 Lottie 失败：无效的参数");
        return;
    }

    ESP_LOGI(TAG, "正在创建 Lottie 动画...");
    lottie_anim = lv_rlottie_create_from_raw(parent, width, height, lottie_data);

    if (lottie_anim) {
        lv_obj_center(lottie_anim);
        lv_obj_add_flag(lottie_anim, LV_OBJ_FLAG_HIDDEN); // 默认隐藏
        ESP_LOGI(TAG, "Lottie 动画创建成功");
    } else {
        ESP_LOGE(TAG, "创建 Lottie 动画失败");
    }
}

void app_lottie_show(bool show)
{
    if (lottie_anim == NULL) {
        ESP_LOGW(TAG, "Lottie 对象不存在，无法显示/隐藏");
        return;
    }

    if (show) {
        lv_obj_clear_flag(lottie_anim, LV_OBJ_FLAG_HIDDEN);
        ESP_LOGI(TAG, "显示 Lottie 动画");
    } else {
        lv_obj_add_flag(lottie_anim, LV_OBJ_FLAG_HIDDEN);
        ESP_LOGI(TAG, "隐藏 Lottie 动画");
    }
}

void app_lottie_delete(void)
{
    if (lottie_anim) {
        lv_obj_del(lottie_anim);
        lottie_anim = NULL;
        ESP_LOGI(TAG, "Lottie 动画已删除");
    }
}