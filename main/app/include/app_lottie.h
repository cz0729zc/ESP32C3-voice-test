#ifndef APP_LOTTIE_H
#define APP_LOTTIE_H

#include "lvgl.h"
#include <stdbool.h>

/**
 * @brief 初始化Lottie动画模块
 *
 */
void app_lottie_init(void);

/**
 * @brief 创建一个Lottie动画对象
 *
 * @param parent 父对象
 * @param lottie_data Lottie JSON数据的指针 (C数组)
 * @param width 动画宽度
 * @param height 动画高度
 * @return esp_err_t
 */
void app_lottie_create(lv_obj_t *parent, const char *lottie_data, lv_coord_t width, lv_coord_t height);

/**
 * @brief 控制Lottie动画的显示或隐藏
 *
 * @param show true: 显示, false: 隐藏
 */
void app_lottie_show(bool show);

/**
 * @brief 删除并清理Lottie动画资源
 *
 */
void app_lottie_delete(void);

#endif // APP_LOTTIE_H