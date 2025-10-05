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
LV_IMAGE_DECLARE(sad_animimg_1sad_0);
LV_IMAGE_DECLARE(sad_animimg_1sad_01);
LV_IMAGE_DECLARE(sad_animimg_1sad_02);
LV_IMAGE_DECLARE(sad_animimg_1sad_03);
LV_IMAGE_DECLARE(sad_animimg_1sad_04);
LV_IMAGE_DECLARE(sad_animimg_1sad_05);
LV_IMAGE_DECLARE(sad_animimg_1sad_06);
LV_IMAGE_DECLARE(sad_animimg_1sad_07);
LV_IMAGE_DECLARE(sad_animimg_1sad_08);
LV_IMAGE_DECLARE(sad_animimg_1sad_09);
LV_IMAGE_DECLARE(sad_animimg_1sad_10);
LV_IMAGE_DECLARE(sad_animimg_1sad_11);
LV_IMAGE_DECLARE(sad_animimg_1sad_12);
LV_IMAGE_DECLARE(sad_animimg_1sad_13);
LV_IMAGE_DECLARE(sad_animimg_1sad_14);
LV_IMAGE_DECLARE(sad_animimg_1sad_15);
LV_IMAGE_DECLARE(sad_animimg_1sad_16);
LV_IMAGE_DECLARE(sad_animimg_1sad_17);
LV_IMAGE_DECLARE(sad_animimg_1sad_18);
LV_IMAGE_DECLARE(sad_animimg_1sad_19);
LV_IMAGE_DECLARE(sad_animimg_1sad_20);
LV_IMAGE_DECLARE(sad_animimg_1sad_21);
LV_IMAGE_DECLARE(sad_animimg_1sad_22);
LV_IMAGE_DECLARE(sad_animimg_1sad_23);
LV_IMAGE_DECLARE(sad_animimg_1sad_24);
LV_IMAGE_DECLARE(sad_animimg_1sad_25);
LV_IMAGE_DECLARE(sad_animimg_1sad_26);
LV_IMAGE_DECLARE(sad_animimg_1sad_27);
LV_IMAGE_DECLARE(sad_animimg_1sad_28);
LV_IMAGE_DECLARE(sad_animimg_1sad_29);
LV_IMAGE_DECLARE(sad_animimg_1sad_30);
LV_IMAGE_DECLARE(sad_animimg_1sad_31);
LV_IMAGE_DECLARE(sad_animimg_1sad_32);
LV_IMAGE_DECLARE(sad_animimg_1sad_33);
LV_IMAGE_DECLARE(sad_animimg_1sad_34);
LV_IMAGE_DECLARE(sad_animimg_1sad_35);
LV_IMAGE_DECLARE(sad_animimg_1sad_36);
LV_IMAGE_DECLARE(sad_animimg_1sad_37);
LV_IMAGE_DECLARE(sad_animimg_1sad_38);
LV_IMAGE_DECLARE(sad_animimg_1sad_39);
LV_IMAGE_DECLARE(sad_animimg_1sad_40);
LV_IMAGE_DECLARE(sad_animimg_1sad_41);
LV_IMAGE_DECLARE(sad_animimg_1sad_42);
LV_IMAGE_DECLARE(sad_animimg_1sad_43);
LV_IMAGE_DECLARE(sad_animimg_1sad_44);
LV_IMAGE_DECLARE(sad_animimg_1sad_45);
LV_IMAGE_DECLARE(sad_animimg_1sad_46);
LV_IMAGE_DECLARE(sad_animimg_1sad_47);
LV_IMAGE_DECLARE(sad_animimg_1sad_48);
LV_IMAGE_DECLARE(sad_animimg_1sad_49);
LV_IMAGE_DECLARE(danger_animimg_1danger_0);
LV_IMAGE_DECLARE(danger_animimg_1danger_01);
LV_IMAGE_DECLARE(danger_animimg_1danger_02);
LV_IMAGE_DECLARE(danger_animimg_1danger_03);
LV_IMAGE_DECLARE(danger_animimg_1danger_04);
LV_IMAGE_DECLARE(danger_animimg_1danger_05);
LV_IMAGE_DECLARE(danger_animimg_1danger_06);
LV_IMAGE_DECLARE(danger_animimg_1danger_07);
LV_IMAGE_DECLARE(danger_animimg_1danger_08);
LV_IMAGE_DECLARE(danger_animimg_1danger_09);
LV_IMAGE_DECLARE(danger_animimg_1danger_10);
LV_IMAGE_DECLARE(danger_animimg_1danger_11);
LV_IMAGE_DECLARE(danger_animimg_1danger_12);
LV_IMAGE_DECLARE(danger_animimg_1danger_13);
LV_IMAGE_DECLARE(danger_animimg_1danger_14);
LV_IMAGE_DECLARE(danger_animimg_1danger_15);
LV_IMAGE_DECLARE(danger_animimg_1danger_16);
LV_IMAGE_DECLARE(danger_animimg_1danger_17);
LV_IMAGE_DECLARE(danger_animimg_1danger_18);
LV_IMAGE_DECLARE(danger_animimg_1danger_19);
LV_IMAGE_DECLARE(danger_animimg_1danger_20);
LV_IMAGE_DECLARE(danger_animimg_1danger_21);
LV_IMAGE_DECLARE(danger_animimg_1danger_22);
LV_IMAGE_DECLARE(danger_animimg_1danger_23);
LV_IMAGE_DECLARE(danger_animimg_1danger_24);
LV_IMAGE_DECLARE(danger_animimg_1danger_25);
LV_IMAGE_DECLARE(danger_animimg_1danger_26);
LV_IMAGE_DECLARE(danger_animimg_1danger_27);
LV_IMAGE_DECLARE(danger_animimg_1danger_28);
LV_IMAGE_DECLARE(danger_animimg_1danger_29);
LV_IMAGE_DECLARE(danger_animimg_1danger_30);
LV_IMAGE_DECLARE(danger_animimg_1danger_31);
LV_IMAGE_DECLARE(danger_animimg_1danger_32);
LV_IMAGE_DECLARE(danger_animimg_1danger_33);
LV_IMAGE_DECLARE(danger_animimg_1danger_34);
LV_IMAGE_DECLARE(danger_animimg_1danger_35);
LV_IMAGE_DECLARE(danger_animimg_1danger_36);
LV_IMAGE_DECLARE(danger_animimg_1danger_37);
LV_IMAGE_DECLARE(danger_animimg_1danger_38);
LV_IMAGE_DECLARE(danger_animimg_1danger_39);
LV_IMAGE_DECLARE(danger_animimg_1danger_40);
LV_IMAGE_DECLARE(danger_animimg_1danger_41);
LV_IMAGE_DECLARE(danger_animimg_1danger_42);
LV_IMAGE_DECLARE(danger_animimg_1danger_43);
LV_IMAGE_DECLARE(danger_animimg_1danger_44);
LV_IMAGE_DECLARE(danger_animimg_1danger_45);
LV_IMAGE_DECLARE(danger_animimg_1danger_46);
LV_IMAGE_DECLARE(danger_animimg_1danger_47);
LV_IMAGE_DECLARE(danger_animimg_1danger_48);
LV_IMAGE_DECLARE(danger_animimg_1danger_49);
LV_IMAGE_DECLARE(danger_animimg_1danger_50);
LV_IMAGE_DECLARE(danger_animimg_1danger_51);
LV_IMAGE_DECLARE(danger_animimg_1danger_52);
LV_IMAGE_DECLARE(danger_animimg_1danger_53);
LV_IMAGE_DECLARE(danger_animimg_1danger_54);
LV_IMAGE_DECLARE(danger_animimg_1danger_55);
LV_IMAGE_DECLARE(danger_animimg_1danger_56);
LV_IMAGE_DECLARE(danger_animimg_1danger_57);
LV_IMAGE_DECLARE(danger_animimg_1danger_58);
LV_IMAGE_DECLARE(danger_animimg_1danger_59);
LV_IMAGE_DECLARE(danger_animimg_1danger_60);
LV_IMAGE_DECLARE(danger_animimg_1danger_61);
LV_IMAGE_DECLARE(danger_animimg_1danger_62);
LV_IMAGE_DECLARE(danger_animimg_1danger_63);
LV_IMAGE_DECLARE(danger_animimg_1danger_64);
LV_IMAGE_DECLARE(danger_animimg_1danger_65);
LV_IMAGE_DECLARE(danger_animimg_1danger_66);
LV_IMAGE_DECLARE(danger_animimg_1danger_67);
LV_IMAGE_DECLARE(danger_animimg_1danger_68);
LV_IMAGE_DECLARE(danger_animimg_1danger_69);
LV_IMAGE_DECLARE(danger_animimg_1danger_70);
LV_IMAGE_DECLARE(danger_animimg_1danger_71);
LV_IMAGE_DECLARE(danger_animimg_1danger_72);
LV_IMAGE_DECLARE(danger_animimg_1danger_73);
LV_IMAGE_DECLARE(danger_animimg_1danger_74);
LV_IMAGE_DECLARE(danger_animimg_1danger_75);
LV_IMAGE_DECLARE(danger_animimg_1danger_76);
LV_IMAGE_DECLARE(danger_animimg_1danger_77);
LV_IMAGE_DECLARE(danger_animimg_1danger_78);
LV_IMAGE_DECLARE(danger_animimg_1danger_79);
LV_IMAGE_DECLARE(danger_animimg_1danger_80);
LV_IMAGE_DECLARE(danger_animimg_1danger_81);
LV_IMAGE_DECLARE(danger_animimg_1danger_82);
LV_IMAGE_DECLARE(danger_animimg_1danger_83);
LV_IMAGE_DECLARE(danger_animimg_1danger_84);
LV_IMAGE_DECLARE(danger_animimg_1danger_85);
LV_IMAGE_DECLARE(danger_animimg_1danger_86);
LV_IMAGE_DECLARE(danger_animimg_1danger_87);
LV_IMAGE_DECLARE(danger_animimg_1danger_88);
LV_IMAGE_DECLARE(danger_animimg_1danger_89);



#ifdef __cplusplus
}
#endif
#endif
