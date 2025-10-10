/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef WIDGET_INIT_H
#define WIDGET_INIT_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"
#include "gui_guider.h"

__attribute__((unused)) void kb_event_cb(lv_event_t *e);
__attribute__((unused)) void ta_event_cb(lv_event_t *e);
#if LV_USE_ANALOGCLOCK != 0
void clock_count(int *hour, int *min, int *sec);
void digital_clock_count(int * hour, int * minute, int * seconds, char * meridiem);
#endif


extern const lv_image_dsc_t * E_2_animimg_1_imgs[40];
extern const lv_image_dsc_t * E_5_animimg_1_imgs[40];
extern const lv_image_dsc_t * E_7_animimg_1_imgs[40];
extern const lv_image_dsc_t * E_8_animimg_1_imgs[60];
extern const lv_image_dsc_t * E_10_animimg_1_imgs[40];
extern const lv_image_dsc_t * E_13_animimg_1_imgs[40];
extern const lv_image_dsc_t * E_14_animimg_1_imgs[40];
extern const lv_image_dsc_t * E_15_animimg_1_imgs[40];
extern const lv_image_dsc_t * E_16_animimg_1_imgs[40];
extern const lv_image_dsc_t * E_17_animimg_1_imgs[40];


#ifdef __cplusplus
}
#endif
#endif
