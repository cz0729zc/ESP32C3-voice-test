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



static void smile_timer_cb(lv_timer_t *timer)
{
    ui_load_scr_animation(&guider_ui, &guider_ui.sad, guider_ui.sad_del, &guider_ui.smile_del, setup_scr_sad, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, true, true);
}

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


    lv_timer_t *timer = lv_timer_create(smile_timer_cb, 5000, NULL);
    lv_timer_set_repeat_count(timer, 1);

    //Update current screen layout.
    lv_obj_update_layout(ui->smile);

}
