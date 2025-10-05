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
    &smile_animimg_1Robot_Happy_floyd,
    &smile_animimg_1Robot_Happy_01_floyd,
    &smile_animimg_1Robot_Happy_02_floyd,
    &smile_animimg_1Robot_Happy_03_floyd,
    &smile_animimg_1Robot_Happy_04_floyd,
    &smile_animimg_1Robot_Happy_05_floyd,
    &smile_animimg_1Robot_Happy_06_floyd,
    &smile_animimg_1Robot_Happy_07_floyd,
    &smile_animimg_1Robot_Happy_08_floyd,
    &smile_animimg_1Robot_Happy_09_floyd,
    &smile_animimg_1Robot_Happy_10_floyd,
    &smile_animimg_1Robot_Happy_11_floyd,
    &smile_animimg_1Robot_Happy_12_floyd,
    &smile_animimg_1Robot_Happy_13_floyd,
    &smile_animimg_1Robot_Happy_14_floyd,
    &smile_animimg_1Robot_Happy_15_floyd,
    &smile_animimg_1Robot_Happy_16_floyd,
    &smile_animimg_1Robot_Happy_17_floyd,
    &smile_animimg_1Robot_Happy_18_floyd,
    &smile_animimg_1Robot_Happy_19_floyd,
    &smile_animimg_1Robot_Happy_20_floyd,
    &smile_animimg_1Robot_Happy_21_floyd,
    &smile_animimg_1Robot_Happy_22_floyd,
    &smile_animimg_1Robot_Happy_23_floyd,
    &smile_animimg_1Robot_Happy_24_floyd,
    &smile_animimg_1Robot_Happy_25_floyd,
    &smile_animimg_1Robot_Happy_26_floyd,
    &smile_animimg_1Robot_Happy_27_floyd,
    &smile_animimg_1Robot_Happy_28_floyd,
    &smile_animimg_1Robot_Happy_29_floyd,
    &smile_animimg_1Robot_Happy_30_floyd,
    &smile_animimg_1Robot_Happy_31_floyd,
    &smile_animimg_1Robot_Happy_32_floyd,
    &smile_animimg_1Robot_Happy_33_floyd,
    &smile_animimg_1Robot_Happy_34_floyd,
    &smile_animimg_1Robot_Happy_35_floyd,
    &smile_animimg_1Robot_Happy_36_floyd,
    &smile_animimg_1Robot_Happy_37_floyd,
    &smile_animimg_1Robot_Happy_38_floyd,
    &smile_animimg_1Robot_Happy_39_floyd,
    &smile_animimg_1Robot_Happy_40_floyd,
    &smile_animimg_1Robot_Happy_41_floyd,
    &smile_animimg_1Robot_Happy_42_floyd,
    &smile_animimg_1Robot_Happy_43_floyd,
    &smile_animimg_1Robot_Happy_44_floyd,
    &smile_animimg_1Robot_Happy_45_floyd,
    &smile_animimg_1Robot_Happy_46_floyd,
    &smile_animimg_1Robot_Happy_47_floyd,
    &smile_animimg_1Robot_Happy_48_floyd,
    &smile_animimg_1Robot_Happy_49_floyd,
    &smile_animimg_1Robot_Happy_50_floyd,
    &smile_animimg_1Robot_Happy_51_floyd,
    &smile_animimg_1Robot_Happy_52_floyd,
    &smile_animimg_1Robot_Happy_53_floyd,
    &smile_animimg_1Robot_Happy_54_floyd,
    &smile_animimg_1Robot_Happy_55_floyd,
    &smile_animimg_1Robot_Happy_56_floyd,
    &smile_animimg_1Robot_Happy_57_floyd,
    &smile_animimg_1Robot_Happy_58_floyd,
    &smile_animimg_1Robot_Happy_59_floyd,
};
const lv_image_dsc_t * sad_animimg_1_imgs[50] = {
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
    &sad_animimg_1sad_45,
    &sad_animimg_1sad_46,
    &sad_animimg_1sad_47,
    &sad_animimg_1sad_48,
    &sad_animimg_1sad_49,
};
const lv_image_dsc_t * danger_animimg_1_imgs[90] = {
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
    &danger_animimg_1danger_30,
    &danger_animimg_1danger_31,
    &danger_animimg_1danger_32,
    &danger_animimg_1danger_33,
    &danger_animimg_1danger_34,
    &danger_animimg_1danger_35,
    &danger_animimg_1danger_36,
    &danger_animimg_1danger_37,
    &danger_animimg_1danger_38,
    &danger_animimg_1danger_39,
    &danger_animimg_1danger_40,
    &danger_animimg_1danger_41,
    &danger_animimg_1danger_42,
    &danger_animimg_1danger_43,
    &danger_animimg_1danger_44,
    &danger_animimg_1danger_45,
    &danger_animimg_1danger_46,
    &danger_animimg_1danger_47,
    &danger_animimg_1danger_48,
    &danger_animimg_1danger_49,
    &danger_animimg_1danger_50,
    &danger_animimg_1danger_51,
    &danger_animimg_1danger_52,
    &danger_animimg_1danger_53,
    &danger_animimg_1danger_54,
    &danger_animimg_1danger_55,
    &danger_animimg_1danger_56,
    &danger_animimg_1danger_57,
    &danger_animimg_1danger_58,
    &danger_animimg_1danger_59,
    &danger_animimg_1danger_60,
    &danger_animimg_1danger_61,
    &danger_animimg_1danger_62,
    &danger_animimg_1danger_63,
    &danger_animimg_1danger_64,
    &danger_animimg_1danger_65,
    &danger_animimg_1danger_66,
    &danger_animimg_1danger_67,
    &danger_animimg_1danger_68,
    &danger_animimg_1danger_69,
    &danger_animimg_1danger_70,
    &danger_animimg_1danger_71,
    &danger_animimg_1danger_72,
    &danger_animimg_1danger_73,
    &danger_animimg_1danger_74,
    &danger_animimg_1danger_75,
    &danger_animimg_1danger_76,
    &danger_animimg_1danger_77,
    &danger_animimg_1danger_78,
    &danger_animimg_1danger_79,
    &danger_animimg_1danger_80,
    &danger_animimg_1danger_81,
    &danger_animimg_1danger_82,
    &danger_animimg_1danger_83,
    &danger_animimg_1danger_84,
    &danger_animimg_1danger_85,
    &danger_animimg_1danger_86,
    &danger_animimg_1danger_87,
    &danger_animimg_1danger_88,
    &danger_animimg_1danger_89,
};
