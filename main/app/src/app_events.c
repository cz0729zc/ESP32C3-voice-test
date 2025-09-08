#include "app_events.h"

// 将全局事件组的定义放在这里
EventGroupHandle_t g_action_event_group;

/**
 * @brief 初始化应用事件模块
 * @details 创建并初始化全局事件组
 */
void app_events_init(void)
{
    g_action_event_group = xEventGroupCreate();
    if (g_action_event_group == NULL) {
        // 在实际产品中，这里应该有更健壮的错误处理
    }
}