/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"


typedef struct
{
  
	lv_obj_t *smile;
	bool smile_del;
	lv_obj_t *smile_animimg_1;
	lv_obj_t *sad;
	bool sad_del;
	lv_obj_t *sad_animimg_1;
	lv_obj_t *danger;
	bool danger_del;
	lv_obj_t *danger_animimg_1;
}lv_ui;

typedef void (*ui_setup_scr_t)(lv_ui * ui);

void ui_init_style(lv_style_t * style);

void ui_load_scr_animation(lv_ui *ui, lv_obj_t ** new_scr, bool new_scr_del, bool * old_scr_del, ui_setup_scr_t setup_scr,
                           lv_screen_load_anim_t anim_type, uint32_t time, uint32_t delay, bool is_clean, bool auto_del);

void ui_animation(void * var, uint32_t duration, int32_t delay, int32_t start_value, int32_t end_value, lv_anim_path_cb_t path_cb,
                  uint32_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time, uint32_t playback_delay,
                  lv_anim_exec_xcb_t exec_cb, lv_anim_start_cb_t start_cb, lv_anim_completed_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);


void init_scr_del_flag(lv_ui *ui);

void setup_bottom_layer(void);

void setup_ui(lv_ui *ui);

void video_play(lv_ui *ui);

void init_keyboard(lv_ui *ui);

extern lv_ui guider_ui;


void setup_scr_smile(lv_ui *ui);
void setup_scr_sad(lv_ui *ui);
void setup_scr_danger(lv_ui *ui);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_01_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_02_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_03_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_04_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_05_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_06_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_07_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_08_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_09_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_10_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_11_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_12_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_13_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_14_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_15_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_16_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_17_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_18_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_19_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_20_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_21_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_22_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_23_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_24_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_25_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_26_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_27_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_28_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_29_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_30_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_31_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_32_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_33_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_34_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_35_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_36_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_37_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_38_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_39_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_40_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_41_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_42_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_43_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_44_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_45_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_46_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_47_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_48_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_49_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_50_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_51_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_52_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_53_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_54_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_55_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_56_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_57_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_58_floyd);
LV_IMAGE_DECLARE(smile_animimg_1Robot_Happy_59_floyd);
LV_IMAGE_DECLARE(sad_animimg_1sad_0_floyd);
LV_IMAGE_DECLARE(sad_animimg_1sad_01_floyd);
LV_IMAGE_DECLARE(sad_animimg_1sad_02_floyd);
LV_IMAGE_DECLARE(sad_animimg_1sad_03_floyd);
LV_IMAGE_DECLARE(sad_animimg_1sad_04_floyd);
LV_IMAGE_DECLARE(sad_animimg_1sad_05_floyd);
LV_IMAGE_DECLARE(sad_animimg_1sad_06_floyd);
LV_IMAGE_DECLARE(sad_animimg_1sad_07_floyd);
LV_IMAGE_DECLARE(sad_animimg_1sad_08_floyd);
LV_IMAGE_DECLARE(sad_animimg_1sad_09_floyd);
LV_IMAGE_DECLARE(sad_animimg_1sad_10_floyd);
LV_IMAGE_DECLARE(sad_animimg_1sad_11_floyd);
LV_IMAGE_DECLARE(sad_animimg_1sad_12_floyd);
LV_IMAGE_DECLARE(sad_animimg_1sad_13_floyd);
LV_IMAGE_DECLARE(sad_animimg_1sad_14_floyd);
LV_IMAGE_DECLARE(sad_animimg_1sad_15_floyd);
LV_IMAGE_DECLARE(sad_animimg_1sad_16_floyd);
LV_IMAGE_DECLARE(sad_animimg_1sad_17_floyd);
LV_IMAGE_DECLARE(sad_animimg_1sad_18_floyd);
LV_IMAGE_DECLARE(sad_animimg_1sad_19_floyd);
LV_IMAGE_DECLARE(sad_animimg_1sad_20_floyd);
LV_IMAGE_DECLARE(sad_animimg_1sad_21_floyd);
LV_IMAGE_DECLARE(sad_animimg_1sad_22_floyd);
LV_IMAGE_DECLARE(sad_animimg_1sad_23_floyd);
LV_IMAGE_DECLARE(sad_animimg_1sad_24_floyd);
LV_IMAGE_DECLARE(sad_animimg_1sad_25_floyd);
LV_IMAGE_DECLARE(sad_animimg_1sad_26_floyd);
LV_IMAGE_DECLARE(sad_animimg_1sad_27_floyd);
LV_IMAGE_DECLARE(sad_animimg_1sad_28_floyd);
LV_IMAGE_DECLARE(sad_animimg_1sad_29_floyd);
LV_IMAGE_DECLARE(sad_animimg_1sad_30_floyd);
LV_IMAGE_DECLARE(sad_animimg_1sad_31_floyd);
LV_IMAGE_DECLARE(sad_animimg_1sad_32_floyd);
LV_IMAGE_DECLARE(sad_animimg_1sad_33_floyd);
LV_IMAGE_DECLARE(sad_animimg_1sad_34_floyd);
LV_IMAGE_DECLARE(sad_animimg_1sad_35_floyd);
LV_IMAGE_DECLARE(sad_animimg_1sad_36_floyd);
LV_IMAGE_DECLARE(sad_animimg_1sad_37_floyd);
LV_IMAGE_DECLARE(sad_animimg_1sad_38_floyd);
LV_IMAGE_DECLARE(sad_animimg_1sad_39_floyd);
LV_IMAGE_DECLARE(sad_animimg_1sad_40_floyd);
LV_IMAGE_DECLARE(sad_animimg_1sad_41_floyd);
LV_IMAGE_DECLARE(sad_animimg_1sad_42_floyd);
LV_IMAGE_DECLARE(sad_animimg_1sad_43_floyd);
LV_IMAGE_DECLARE(sad_animimg_1sad_44_floyd);
LV_IMAGE_DECLARE(sad_animimg_1sad_45_floyd);
LV_IMAGE_DECLARE(sad_animimg_1sad_46_floyd);
LV_IMAGE_DECLARE(sad_animimg_1sad_47_floyd);
LV_IMAGE_DECLARE(sad_animimg_1sad_48_floyd);
LV_IMAGE_DECLARE(sad_animimg_1sad_49_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_0_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_01_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_02_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_03_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_04_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_05_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_06_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_07_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_08_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_09_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_10_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_11_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_12_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_13_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_14_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_15_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_16_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_17_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_18_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_19_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_20_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_21_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_22_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_23_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_24_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_25_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_26_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_27_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_28_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_29_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_30_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_31_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_32_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_33_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_34_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_35_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_36_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_37_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_38_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_39_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_40_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_41_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_42_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_43_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_44_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_45_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_46_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_47_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_48_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_49_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_50_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_51_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_52_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_53_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_54_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_55_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_56_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_57_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_58_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_59_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_60_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_61_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_62_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_63_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_64_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_65_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_66_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_67_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_68_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_69_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_70_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_71_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_72_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_73_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_74_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_75_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_76_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_77_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_78_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_79_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_80_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_81_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_82_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_83_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_84_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_85_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_86_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_87_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_88_floyd);
LV_IMAGE_DECLARE(danger_animimg_1danger_89_floyd);



#ifdef __cplusplus
}
#endif
#endif
