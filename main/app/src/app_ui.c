#include "app_ui.h"
#include "esp_log.h"
#include "esp_system.h"
#include "lvgl.h"
#include "esp_lvgl_port.h"

#include "ui_custom/gui_guider.h"
#include "ui_custom/events_init.h"
#include "ui_custom/custom.h"

#include <stdio.h>

static const char *TAG = "app_ui";

// Enum to track the current screen
typedef enum {
    SCREEN_ID_NONE,
    SCREEN_ID_SMILE,
    SCREEN_ID_SAD,
    SCREEN_ID_DANGER,
} screen_id_t;

static screen_id_t g_current_screen = SCREEN_ID_DANGER; // Default screen set by setup_ui

// Helper to get the delete flag pointer for the current screen
static bool* get_current_screen_del_flag(void)
{
    switch (g_current_screen) {
        case SCREEN_ID_SMILE:
            return &guider_ui.smile_del;
        case SCREEN_ID_SAD:
            return &guider_ui.sad_del;
        case SCREEN_ID_DANGER:
            return &guider_ui.danger_del;
        default:
            // For the very first transition, there's no old screen.
            // Return a pointer to a static bool that is true, so the (non-existent) old screen is marked for deletion.
            static bool first_time_del = true;
            return &first_time_del;
    }
}

// Generic screen switching function
static void switch_to_screen(screen_id_t screen_id)
{
    if (lvgl_port_lock(0)) {
        if (g_current_screen == screen_id) {
            ESP_LOGI(TAG, "Already on the target screen, skipping switch.");
            lvgl_port_unlock();
            return;
        }

        ESP_LOGI(TAG, "Memory before switch: %zu bytes", (size_t)esp_get_free_heap_size());

        bool *old_scr_del = get_current_screen_del_flag();
        lv_obj_t **new_scr = NULL;
        ui_setup_scr_t setup_scr = NULL;
        const char *scr_name = "UNKNOWN";
        bool new_scr_del_val = false;

        switch (screen_id) {
            case SCREEN_ID_SMILE:
                new_scr = &guider_ui.smile;
                setup_scr = setup_scr_smile;
                new_scr_del_val = guider_ui.smile_del;
                scr_name = "SMILE";
                break;
            case SCREEN_ID_SAD:
                new_scr = &guider_ui.sad;
                setup_scr = setup_scr_sad;
                new_scr_del_val = guider_ui.sad_del;
                scr_name = "SAD";
                break;
            case SCREEN_ID_DANGER:
                new_scr = &guider_ui.danger;
                setup_scr = setup_scr_danger;
                new_scr_del_val = guider_ui.danger_del;
                scr_name = "DANGER";
                break;
            default:
                ESP_LOGE(TAG, "Invalid screen ID: %d", screen_id);
                // Restore memory log on failure
                ESP_LOGI(TAG, "Memory after failed switch attempt: %zu bytes", (size_t)esp_get_free_heap_size());
                lvgl_port_unlock();
                return;
        }

        ESP_LOGI(TAG, "Switching from screen %d to %s screen", g_current_screen, scr_name);

        ui_load_scr_animation(&guider_ui, new_scr, new_scr_del_val, old_scr_del, setup_scr, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, true, true);

        g_current_screen = screen_id;

        ESP_LOGI(TAG, "Memory after switch: %zu bytes", (size_t)esp_get_free_heap_size());
        
        lvgl_port_unlock();
    }
}


esp_err_t app_ui_init(void)
{
    ESP_LOGI(TAG, "UI Application Init");

    // setup_ui already handles the creation and loading of the initial screen (danger).
    // It also calls init_scr_del_flag.
    setup_ui(&guider_ui);
    events_init(&guider_ui); // events_init is currently empty but keep it for future use.

    ESP_LOGI(TAG, "UI Init Finished, default screen is set by setup_ui (DANGER).");
    ESP_LOGI(TAG, "Initial memory: %d bytes", (size_t)esp_get_free_heap_size());

    // Create a timer to cycle through screens for testing
    void ui_test_timer_cb(lv_timer_t *timer);
    lv_timer_create(ui_test_timer_cb, 5000, NULL);
    ESP_LOGI(TAG, "UI test timer created, will switch screens every 5 seconds.");

    return ESP_OK;
}

void app_ui_show_uniform_speed(int index)
{
    ESP_LOGI(TAG, "UI Update: Uniform Speed -> SMILE");
    switch_to_screen(SCREEN_ID_SMILE);
}

void app_ui_show_turn_left_start(void)
{
    ESP_LOGI(TAG, "UI Update: Turn Left Start -> DANGER");
    switch_to_screen(SCREEN_ID_DANGER);
}

void app_ui_show_turn_left_end(void)
{
    ESP_LOGI(TAG, "UI Update: Turn Left End -> SAD");
    switch_to_screen(SCREEN_ID_SAD);
}

void app_ui_show_turn_right_start(void)
{
    ESP_LOGI(TAG, "UI Update: Turn Right Start -> SAD");
    switch_to_screen(SCREEN_ID_SAD);
}

void app_ui_show_turn_right_end(void)
{
    ESP_LOGI(TAG, "UI Update: Turn Right End -> DANGER");
    switch_to_screen(SCREEN_ID_DANGER);
}

void app_ui_show_accelerate_start(void)
{
    // TODO: Implement UI for accelerate start
    ESP_LOGI(TAG, "UI Update: Accelerate Start (Not Implemented)");
}

void app_ui_show_accelerate_end(void)
{
    // TODO: Implement UI for accelerate end
    ESP_LOGI(TAG, "UI Update: Accelerate End (Not Implemented)");
}

void app_ui_show_brake_start(void)
{
    // TODO: Implement UI for brake start
    ESP_LOGI(TAG, "UI Update: Brake Start (Not Implemented)");
}

void app_ui_show_brake_end(void)
{
    // TODO: Implement UI for brake end
    ESP_LOGI(TAG, "UI Update: Brake End (Not Implemented)");
}

void app_ui_show_turn_left_hard(void)
{
    ESP_LOGI(TAG, "UI Update: Hard Turn Left -> DANGER");
    switch_to_screen(SCREEN_ID_DANGER);
}

void app_ui_show_turn_right_hard(void)
{
    ESP_LOGI(TAG, "UI Update: Hard Turn Right -> SAD");
    switch_to_screen(SCREEN_ID_SAD);
}

// Timer callback for automated UI testing
void ui_test_timer_cb(lv_timer_t *timer)
{
    static int next_screen_index = 0;
    screen_id_t screens_to_cycle[] = {SCREEN_ID_SMILE, SCREEN_ID_SAD, SCREEN_ID_DANGER};
    
    // Log memory usage *before* the switch.
    // At this point (5s after the last switch), the previous screen's resources should have been fully released.
    ESP_LOGI(TAG, "[Test Timer] Memory before next switch: %zu bytes", (size_t)esp_get_free_heap_size());

    screen_id_t next_screen = screens_to_cycle[next_screen_index];
    
    ESP_LOGI(TAG, "[Test Timer] Switching to screen index %d", next_screen_index);
    
    // Manually call the corresponding function to trigger the switch
    switch(next_screen) {
        case SCREEN_ID_SMILE:
            app_ui_show_uniform_speed(0);
            break;
        case SCREEN_ID_SAD:
            app_ui_show_turn_left_end();
            break;
        case SCREEN_ID_DANGER:
            app_ui_show_turn_left_start();
            break;
        default:
            break;
    }

    next_screen_index = (next_screen_index + 1) % (sizeof(screens_to_cycle) / sizeof(screen_id_t));
}