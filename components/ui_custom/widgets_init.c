/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include "gui_guider.h"
#include "widgets_init.h"
#include <stdlib.h>
#include <string.h>


__attribute__((unused)) void kb_event_cb (lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *kb = lv_event_get_target(e);
    if(code == LV_EVENT_READY || code == LV_EVENT_CANCEL) {
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }
}

__attribute__((unused)) void ta_event_cb (lv_event_t *e) {
#if LV_USE_KEYBOARD
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    lv_obj_t * kb = lv_event_get_user_data(e);

    if(code == LV_EVENT_FOCUSED) {
        if(lv_indev_get_type(lv_indev_active()) != LV_INDEV_TYPE_KEYPAD) {
            lv_keyboard_set_textarea(kb, ta);
            lv_obj_remove_flag(kb, LV_OBJ_FLAG_HIDDEN);
        }
    } else if(code == LV_EVENT_READY) {
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
        lv_obj_remove_state(ta, LV_STATE_FOCUSED);
        lv_indev_reset(NULL, ta);
    } else if(code == LV_EVENT_DEFOCUSED) {
        lv_keyboard_set_textarea(kb, NULL);
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }
#endif
}

void clock_count(int *hour, int *min, int *sec)
{
    (*sec)++;
    if(*sec == 60)
    {
        *sec = 0;
        (*min)++;
    }
    if(*min == 60)
    {
        *min = 0;
        if(*hour < 12)
        {
            (*hour)++;
        } else {
            (*hour)++;
            *hour = *hour %12;
        }
    }
}

void digital_clock_count(int * hour, int * minute, int * seconds, char * meridiem)
{

    (*seconds)++;
    if(*seconds == 60) {
        *seconds = 0;
        (*minute)++;
    }
    if(*minute == 60) {
        *minute = 0;
        if(*hour < 12) {
            (*hour)++;
        }
        else {
            (*hour)++;
            (*hour) = (*hour) % 12;
        }
    }
    if(*hour == 12 && *seconds == 0 && *minute == 0) {
        if((lv_strcmp(meridiem, "PM") == 0)) {
            lv_strcpy(meridiem, "AM");
        }
        else {
            lv_strcpy(meridiem, "PM");
        }
    }
}


const lv_image_dsc_t * smile_animimg_1_imgs[60] = {
    &smile_animimg_1Robot_Happy,
    &smile_animimg_1Robot_Happy_01,
    &smile_animimg_1Robot_Happy_02,
    &smile_animimg_1Robot_Happy_03,
    &smile_animimg_1Robot_Happy_04,
    &smile_animimg_1Robot_Happy_05,
    &smile_animimg_1Robot_Happy_06,
    &smile_animimg_1Robot_Happy_07,
    &smile_animimg_1Robot_Happy_08,
    &smile_animimg_1Robot_Happy_09,
    &smile_animimg_1Robot_Happy_10,
    &smile_animimg_1Robot_Happy_11,
    &smile_animimg_1Robot_Happy_12,
    &smile_animimg_1Robot_Happy_13,
    &smile_animimg_1Robot_Happy_14,
    &smile_animimg_1Robot_Happy_15,
    &smile_animimg_1Robot_Happy_16,
    &smile_animimg_1Robot_Happy_17,
    &smile_animimg_1Robot_Happy_18,
    &smile_animimg_1Robot_Happy_19,
    &smile_animimg_1Robot_Happy_20,
    &smile_animimg_1Robot_Happy_21,
    &smile_animimg_1Robot_Happy_22,
    &smile_animimg_1Robot_Happy_23,
    &smile_animimg_1Robot_Happy_24,
    &smile_animimg_1Robot_Happy_25,
    &smile_animimg_1Robot_Happy_26,
    &smile_animimg_1Robot_Happy_27,
    &smile_animimg_1Robot_Happy_28,
    &smile_animimg_1Robot_Happy_29,
    &smile_animimg_1Robot_Happy_30,
    &smile_animimg_1Robot_Happy_31,
    &smile_animimg_1Robot_Happy_32,
    &smile_animimg_1Robot_Happy_33,
    &smile_animimg_1Robot_Happy_34,
    &smile_animimg_1Robot_Happy_35,
    &smile_animimg_1Robot_Happy_36,
    &smile_animimg_1Robot_Happy_37,
    &smile_animimg_1Robot_Happy_38,
    &smile_animimg_1Robot_Happy_39,
    &smile_animimg_1Robot_Happy_40,
    &smile_animimg_1Robot_Happy_41,
    &smile_animimg_1Robot_Happy_42,
    &smile_animimg_1Robot_Happy_43,
    &smile_animimg_1Robot_Happy_44,
    &smile_animimg_1Robot_Happy_45,
    &smile_animimg_1Robot_Happy_46,
    &smile_animimg_1Robot_Happy_47,
    &smile_animimg_1Robot_Happy_48,
    &smile_animimg_1Robot_Happy_49,
    &smile_animimg_1Robot_Happy_50,
    &smile_animimg_1Robot_Happy_51,
    &smile_animimg_1Robot_Happy_52,
    &smile_animimg_1Robot_Happy_53,
    &smile_animimg_1Robot_Happy_54,
    &smile_animimg_1Robot_Happy_55,
    &smile_animimg_1Robot_Happy_56,
    &smile_animimg_1Robot_Happy_57,
    &smile_animimg_1Robot_Happy_58,
    &smile_animimg_1Robot_Happy_59,
};
const lv_image_dsc_t * sad_animimg_1_imgs[45] = {
    &sad_animimg_1sad_0,
    &sad_animimg_1sad_01,
    &sad_animimg_1sad_02,
    &sad_animimg_1sad_03,
    &sad_animimg_1sad_04,
    &sad_animimg_1sad_05,
    &sad_animimg_1sad_06,
    &sad_animimg_1sad_07,
    &sad_animimg_1sad_08,
    &sad_animimg_1sad_09,
    &sad_animimg_1sad_10,
    &sad_animimg_1sad_11,
    &sad_animimg_1sad_12,
    &sad_animimg_1sad_13,
    &sad_animimg_1sad_14,
    &sad_animimg_1sad_15,
    &sad_animimg_1sad_16,
    &sad_animimg_1sad_17,
    &sad_animimg_1sad_18,
    &sad_animimg_1sad_19,
    &sad_animimg_1sad_20,
    &sad_animimg_1sad_21,
    &sad_animimg_1sad_22,
    &sad_animimg_1sad_23,
    &sad_animimg_1sad_24,
    &sad_animimg_1sad_25,
    &sad_animimg_1sad_26,
    &sad_animimg_1sad_27,
    &sad_animimg_1sad_28,
    &sad_animimg_1sad_29,
    &sad_animimg_1sad_30,
    &sad_animimg_1sad_31,
    &sad_animimg_1sad_32,
    &sad_animimg_1sad_33,
    &sad_animimg_1sad_34,
    &sad_animimg_1sad_35,
    &sad_animimg_1sad_36,
    &sad_animimg_1sad_37,
    &sad_animimg_1sad_38,
    &sad_animimg_1sad_39,
    &sad_animimg_1sad_40,
    &sad_animimg_1sad_41,
    &sad_animimg_1sad_42,
    &sad_animimg_1sad_43,
    &sad_animimg_1sad_44,
};
const lv_image_dsc_t * danger_animimg_1_imgs[36] = {
    &danger_animimg_1danger_0,
    &danger_animimg_1danger_01,
    &danger_animimg_1danger_02,
    &danger_animimg_1danger_03,
    &danger_animimg_1danger_04,
    &danger_animimg_1danger_05,
    &danger_animimg_1danger_06,
    &danger_animimg_1danger_07,
    &danger_animimg_1danger_08,
    &danger_animimg_1danger_09,
    &danger_animimg_1danger_10,
    &danger_animimg_1danger_11,
    &danger_animimg_1danger_12,
    &danger_animimg_1danger_13,
    &danger_animimg_1danger_14,
    &danger_animimg_1danger_15,
    &danger_animimg_1danger_16,
    &danger_animimg_1danger_17,
    &danger_animimg_1danger_18,
    &danger_animimg_1danger_19,
    &danger_animimg_1danger_20,
    &danger_animimg_1danger_21,
    &danger_animimg_1danger_22,
    &danger_animimg_1danger_23,
    &danger_animimg_1danger_24,
    &danger_animimg_1danger_25,
    &danger_animimg_1danger_26,
    &danger_animimg_1danger_27,
    &danger_animimg_1danger_28,
    &danger_animimg_1danger_29,
};
