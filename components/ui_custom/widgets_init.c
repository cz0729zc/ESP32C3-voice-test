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
    &sad_animimg_1sad_0_floyd,
    &sad_animimg_1sad_01_floyd,
    &sad_animimg_1sad_02_floyd,
    &sad_animimg_1sad_03_floyd,
    &sad_animimg_1sad_04_floyd,
    &sad_animimg_1sad_05_floyd,
    &sad_animimg_1sad_06_floyd,
    &sad_animimg_1sad_07_floyd,
    &sad_animimg_1sad_08_floyd,
    &sad_animimg_1sad_09_floyd,
    &sad_animimg_1sad_10_floyd,
    &sad_animimg_1sad_11_floyd,
    &sad_animimg_1sad_12_floyd,
    &sad_animimg_1sad_13_floyd,
    &sad_animimg_1sad_14_floyd,
    &sad_animimg_1sad_15_floyd,
    &sad_animimg_1sad_16_floyd,
    &sad_animimg_1sad_17_floyd,
    &sad_animimg_1sad_18_floyd,
    &sad_animimg_1sad_19_floyd,
    &sad_animimg_1sad_20_floyd,
    &sad_animimg_1sad_21_floyd,
    &sad_animimg_1sad_22_floyd,
    &sad_animimg_1sad_23_floyd,
    &sad_animimg_1sad_24_floyd,
    &sad_animimg_1sad_25_floyd,
    &sad_animimg_1sad_26_floyd,
    &sad_animimg_1sad_27_floyd,
    &sad_animimg_1sad_28_floyd,
    &sad_animimg_1sad_29_floyd,
    &sad_animimg_1sad_30_floyd,
    &sad_animimg_1sad_31_floyd,
    &sad_animimg_1sad_32_floyd,
    &sad_animimg_1sad_33_floyd,
    &sad_animimg_1sad_34_floyd,
    &sad_animimg_1sad_35_floyd,
    &sad_animimg_1sad_36_floyd,
    &sad_animimg_1sad_37_floyd,
    &sad_animimg_1sad_38_floyd,
    &sad_animimg_1sad_39_floyd,
    &sad_animimg_1sad_40_floyd,
    &sad_animimg_1sad_41_floyd,
    &sad_animimg_1sad_42_floyd,
    &sad_animimg_1sad_43_floyd,
    &sad_animimg_1sad_44_floyd,
    &sad_animimg_1sad_45_floyd,
    &sad_animimg_1sad_46_floyd,
    &sad_animimg_1sad_47_floyd,
    &sad_animimg_1sad_48_floyd,
    &sad_animimg_1sad_49_floyd,
};
const lv_image_dsc_t * danger_animimg_1_imgs[90] = {
    &danger_animimg_1danger_0_floyd,
    &danger_animimg_1danger_01_floyd,
    &danger_animimg_1danger_02_floyd,
    &danger_animimg_1danger_03_floyd,
    &danger_animimg_1danger_04_floyd,
    &danger_animimg_1danger_05_floyd,
    &danger_animimg_1danger_06_floyd,
    &danger_animimg_1danger_07_floyd,
    &danger_animimg_1danger_08_floyd,
    &danger_animimg_1danger_09_floyd,
    &danger_animimg_1danger_10_floyd,
    &danger_animimg_1danger_11_floyd,
    &danger_animimg_1danger_12_floyd,
    &danger_animimg_1danger_13_floyd,
    &danger_animimg_1danger_14_floyd,
    &danger_animimg_1danger_15_floyd,
    &danger_animimg_1danger_16_floyd,
    &danger_animimg_1danger_17_floyd,
    &danger_animimg_1danger_18_floyd,
    &danger_animimg_1danger_19_floyd,
    &danger_animimg_1danger_20_floyd,
    &danger_animimg_1danger_21_floyd,
    &danger_animimg_1danger_22_floyd,
    &danger_animimg_1danger_23_floyd,
    &danger_animimg_1danger_24_floyd,
    &danger_animimg_1danger_25_floyd,
    &danger_animimg_1danger_26_floyd,
    &danger_animimg_1danger_27_floyd,
    &danger_animimg_1danger_28_floyd,
    &danger_animimg_1danger_29_floyd,
    &danger_animimg_1danger_30_floyd,
    &danger_animimg_1danger_31_floyd,
    &danger_animimg_1danger_32_floyd,
    &danger_animimg_1danger_33_floyd,
    &danger_animimg_1danger_34_floyd,
    &danger_animimg_1danger_35_floyd,
    &danger_animimg_1danger_36_floyd,
    &danger_animimg_1danger_37_floyd,
    &danger_animimg_1danger_38_floyd,
    &danger_animimg_1danger_39_floyd,
    &danger_animimg_1danger_40_floyd,
    &danger_animimg_1danger_41_floyd,
    &danger_animimg_1danger_42_floyd,
    &danger_animimg_1danger_43_floyd,
    &danger_animimg_1danger_44_floyd,
    &danger_animimg_1danger_45_floyd,
    &danger_animimg_1danger_46_floyd,
    &danger_animimg_1danger_47_floyd,
    &danger_animimg_1danger_48_floyd,
    &danger_animimg_1danger_49_floyd,
    &danger_animimg_1danger_50_floyd,
    &danger_animimg_1danger_51_floyd,
    &danger_animimg_1danger_52_floyd,
    &danger_animimg_1danger_53_floyd,
    &danger_animimg_1danger_54_floyd,
    &danger_animimg_1danger_55_floyd,
    &danger_animimg_1danger_56_floyd,
    &danger_animimg_1danger_57_floyd,
    &danger_animimg_1danger_58_floyd,
    &danger_animimg_1danger_59_floyd,
    &danger_animimg_1danger_60_floyd,
    &danger_animimg_1danger_61_floyd,
    &danger_animimg_1danger_62_floyd,
    &danger_animimg_1danger_63_floyd,
    &danger_animimg_1danger_64_floyd,
    &danger_animimg_1danger_65_floyd,
    &danger_animimg_1danger_66_floyd,
    &danger_animimg_1danger_67_floyd,
    &danger_animimg_1danger_68_floyd,
    &danger_animimg_1danger_69_floyd,
    &danger_animimg_1danger_70_floyd,
    &danger_animimg_1danger_71_floyd,
    &danger_animimg_1danger_72_floyd,
    &danger_animimg_1danger_73_floyd,
    &danger_animimg_1danger_74_floyd,
    &danger_animimg_1danger_75_floyd,
    &danger_animimg_1danger_76_floyd,
    &danger_animimg_1danger_77_floyd,
    &danger_animimg_1danger_78_floyd,
    &danger_animimg_1danger_79_floyd,
    &danger_animimg_1danger_80_floyd,
    &danger_animimg_1danger_81_floyd,
    &danger_animimg_1danger_82_floyd,
    &danger_animimg_1danger_83_floyd,
    &danger_animimg_1danger_84_floyd,
    &danger_animimg_1danger_85_floyd,
    &danger_animimg_1danger_86_floyd,
    &danger_animimg_1danger_87_floyd,
    &danger_animimg_1danger_88_floyd,
    &danger_animimg_1danger_89_floyd,
};
