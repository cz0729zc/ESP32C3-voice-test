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



void setup_scr_danger(lv_ui *ui)
{
    //Write codes danger
    ui->danger = lv_obj_create(NULL);
    lv_obj_set_size(ui->danger, 240, 240);
    lv_obj_set_scrollbar_mode(ui->danger, LV_SCROLLBAR_MODE_OFF);

    //Write style for danger, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->danger, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->danger, lv_color_hex(0x050000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->danger, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes danger_animimg_1
    ui->danger_animimg_1 = lv_animimg_create(ui->danger);
    lv_obj_set_pos(ui->danger_animimg_1, 70, 70);
    lv_obj_set_size(ui->danger_animimg_1, 100, 100);
    lv_animimg_set_src(ui->danger_animimg_1, (const void **) danger_animimg_1_imgs, 90, false);
    lv_animimg_set_duration(ui->danger_animimg_1, 30*90);
    lv_animimg_set_repeat_count(ui->danger_animimg_1, LV_ANIM_REPEAT_INFINITE);
    lv_animimg_start(ui->danger_animimg_1);

    //The custom code of danger.


    //Update current screen layout.
    lv_obj_update_layout(ui->danger);

}
