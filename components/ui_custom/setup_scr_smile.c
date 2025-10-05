/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"



void setup_scr_smile(lv_ui *ui)
{
    //Write codes smile
    ui->smile = lv_obj_create(NULL);
    lv_obj_set_size(ui->smile, 240, 240);
    lv_obj_set_scrollbar_mode(ui->smile, LV_SCROLLBAR_MODE_OFF);

    //Write style for smile, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->smile, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->smile, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->smile, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smile_animimg_1
    ui->smile_animimg_1 = lv_animimg_create(ui->smile);
    lv_obj_set_pos(ui->smile_animimg_1, 70, 70);
    lv_obj_set_size(ui->smile_animimg_1, 100, 100);
    lv_animimg_set_src(ui->smile_animimg_1, (const void **) smile_animimg_1_imgs, 60);
    lv_animimg_set_duration(ui->smile_animimg_1, 30*60);
    lv_animimg_set_repeat_count(ui->smile_animimg_1, LV_ANIM_REPEAT_INFINITE);
    lv_animimg_start(ui->smile_animimg_1);

    //The custom code of smile.


    //Update current screen layout.
    lv_obj_update_layout(ui->smile);

}
