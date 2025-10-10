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



void setup_scr_E_16(lv_ui *ui)
{
    //Write codes E_16
    ui->E_16 = lv_obj_create(NULL);
    lv_obj_set_size(ui->E_16, 240, 240);
    lv_obj_set_scrollbar_mode(ui->E_16, LV_SCROLLBAR_MODE_OFF);

    //Write style for E_16, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->E_16, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->E_16, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->E_16, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes E_16_animimg_1
    ui->E_16_animimg_1 = lv_animimg_create(ui->E_16);
    lv_obj_set_pos(ui->E_16_animimg_1, 45, 45);
    lv_obj_set_size(ui->E_16_animimg_1, 150, 150);
    lv_animimg_set_src(ui->E_16_animimg_1, (const void **) E_16_animimg_1_imgs, 40, false);
    lv_animimg_set_duration(ui->E_16_animimg_1, 30*40);
    lv_animimg_set_repeat_count(ui->E_16_animimg_1, LV_ANIM_REPEAT_INFINITE);
    lv_animimg_start(ui->E_16_animimg_1);

    //The custom code of E_16.


    //Update current screen layout.
    lv_obj_update_layout(ui->E_16);

}
