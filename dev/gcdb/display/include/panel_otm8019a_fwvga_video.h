/* Copyright (c) 2014-2015, The Linux Foundation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *  * Neither the name of The Linux Foundation nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*---------------------------------------------------------------------------
 * This file is autogenerated file using gcdb parser. Please do not edit it.
 * Update input XML file to add a new entry or update variable in this file
 * VERSION = "1.0"
 *---------------------------------------------------------------------------*/

#ifndef _PANEL_OTM8019A_FWVGA_VIDEO_H_
#define _PANEL_OTM8019A_FWVGA_VIDEO_H_
/*---------------------------------------------------------------------------*/
/* HEADER files                                                              */
/*---------------------------------------------------------------------------*/
#include "panel.h"

/*---------------------------------------------------------------------------*/
/* Panel configuration                                                       */
/*---------------------------------------------------------------------------*/
static struct panel_config otm8019a_fwvga_video_panel_data = {
	"qcom,mdss_dsi_otm8019a_fwvga_video", "dsi:0:", "qcom,mdss-dsi-panel",
	10, 0, "DISPLAY_1", 0, 0, 60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL
};

/*---------------------------------------------------------------------------*/
/* Panel resolution                                                          */
/*---------------------------------------------------------------------------*/
static struct panel_resolution otm8019a_fwvga_video_panel_res = {
	480, 854, 46, 44, 4, 0, 15, 16, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/*---------------------------------------------------------------------------*/
/* Panel color information                                                   */
/*---------------------------------------------------------------------------*/
static struct color_info otm8019a_fwvga_video_color = {
	24, 0, 0xff, 0, 0, 0
};

/*---------------------------------------------------------------------------*/
/* Panel on/off command information                                          */
/*---------------------------------------------------------------------------*/
static char otm8019a_fwvga_video_on_cmd0[] = {
	0x02, 0x00, 0x29, 0xC0,
	0x00, 0x00, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd1[] = {
	0x04, 0x00, 0x29, 0xC0,
	0xFF, 0x80, 0x19, 0x01,
};

static char otm8019a_fwvga_video_on_cmd2[] = {
	0x02, 0x00, 0x29, 0xC0,
	0x00, 0x80, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd3[] = {
	0x03, 0x00, 0x29, 0xC0,
	0xFF, 0x80, 0x19, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd4[] = {
	0x02, 0x00, 0x29, 0xC0,
	0x00, 0xB4, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd5[] = {
	0x02, 0x00, 0x29, 0xC0,
	0xC0, 0x70, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd6[] = {
	0x02, 0x00, 0x29, 0xC0,
	0x00, 0x88, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd7[] = {
	0x02, 0x00, 0x29, 0xC0,
	0xC4, 0x80, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd8[] = {
	0x02, 0x00, 0x29, 0xC0,
	0x00, 0xB6, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd9[] = {
	0x02, 0x00, 0x29, 0xC0,
	0xC0, 0x03, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd10[] = {
	0x02, 0x00, 0x29, 0xC0,
	0x00, 0x82, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd11[] = {
	0x02, 0x00, 0x29, 0xC0,
	0xC5, 0xB0, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd12[] = {
	0x02, 0x00, 0x29, 0xC0,
	0x00, 0x90, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd13[] = {
	0x03, 0x00, 0x29, 0xC0,
	0xC5, 0x6e, 0x76, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd14[] = {
	0x02, 0x00, 0x29, 0xC0,
	0x00, 0x00, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd15[] = {
	0x03, 0x00, 0x29, 0xC0,
	0xD8, 0x6F, 0x6F, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd16[] = {
	0x02, 0x00, 0x29, 0xC0,
	0x00, 0x00, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd17[] = {
	0x02, 0x00, 0x29, 0xC0,
	0xD9, 0x33, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd18[] = {
	0x02, 0x00, 0x29, 0xC0,
	0x00, 0x81, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd19[] = {
	0x02, 0x00, 0x29, 0xC0,
	0xC1, 0x33, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd20[] = {
	0x02, 0x00, 0x29, 0xC0,
	0x00, 0xA3, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd21[] = {
	0x02, 0x00, 0x29, 0xC0,
	0xC0, 0x1B, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd22[] = {
	0x02, 0x00, 0x29, 0xC0,
	0x00, 0x81, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd23[] = {
	0x02, 0x00, 0x29, 0xC0,
	0xC4, 0x83, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd24[] = {
	0x02, 0x00, 0x29, 0xC0,
	0x00, 0x92, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd25[] = {
	0x02, 0x00, 0x29, 0xC0,
	0xC5, 0x01, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd26[] = {
	0x02, 0x00, 0x29, 0xC0,
	0x00, 0xB1, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd27[] = {
	0x02, 0x00, 0x29, 0xC0,
	0xC5, 0xA9, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd28[] = {
	0x02, 0x00, 0x29, 0xC0,
	0x00, 0x80, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd29[] = {
	0x02, 0x00, 0x29, 0xC0,
	0xC4, 0x30, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd30[] = {
	0x02, 0x00, 0x29, 0xC0,
	0x00, 0xA0, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd31[] = {
	0x02, 0x00, 0x29, 0xC0,
	0xC1, 0xe8, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd32[] = {
	0x02, 0x00, 0x29, 0xC0,
	0x00, 0x80, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd33[] = {
	0x02, 0x00, 0x29, 0xC0,
	0xc1, 0x03, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd34[] = {
	0x02, 0x00, 0x29, 0xC0,
	0x00, 0x98, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd35[] = {
	0x02, 0x00, 0x29, 0xC0,
	0xc0, 0x00, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd36[] = {
	0x02, 0x00, 0x29, 0xC0,
	0x00, 0xa9, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd37[] = {
	0x02, 0x00, 0x29, 0xC0,
	0xc0, 0x06, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd38[] = {
	0x02, 0x00, 0x29, 0xC0,
	0x00, 0xb0, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd39[] = {
	0x04, 0x00, 0x29, 0xC0,
	0xc1, 0x20, 0x00, 0x00,
};

static char otm8019a_fwvga_video_on_cmd40[] = {
	0x02, 0x00, 0x29, 0xC0,
	0x00, 0xe1, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd41[] = {
	0x03, 0x00, 0x29, 0xC0,
	0xc0, 0x40, 0x18, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd42[] = {
	0x02, 0x00, 0x29, 0xC0,
	0x00, 0x90, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd43[] = {
	0x02, 0x00, 0x29, 0xC0,
	0xb6, 0xB4, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd44[] = {
	0x02, 0x00, 0x29, 0xC0,
	0x00, 0x90, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd45[] = {
	0x02, 0x00, 0x29, 0xC0,
	0xB3, 0x02, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd46[] = {
	0x02, 0x00, 0x29, 0xC0,
	0x00, 0x92, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd47[] = {
	0x02, 0x00, 0x29, 0xC0,
	0xB3, 0x45, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd48[] = {
	0x02, 0x00, 0x29, 0xC0,
	0x00, 0x80, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd49[] = {
	0x0a, 0x00, 0x29, 0xC0,
	0xC0, 0x00, 0x58, 0x00,
	0x15, 0x15, 0x00, 0x58,
	0x15, 0x15, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd50[] = {
	0x02, 0x00, 0x29, 0xC0,
	0x00, 0x90, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd51[] = {
	0x07, 0x00, 0x29, 0xC0,
	0xC0, 0x00, 0x15, 0x00,
	0x00, 0x00, 0x03, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd52[] = {
	0x02, 0x00, 0x29, 0xC0,
	0x00, 0x80, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd53[] = {
	0x07, 0x00, 0x29, 0xC0,
	0xCE, 0x8B, 0x03, 0x03,
	0x8A, 0x03, 0x03, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd54[] = {
	0x02, 0x00, 0x29, 0xC0,
	0x00, 0x90, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd55[] = {
	0x0F, 0x00, 0x29, 0xC0,
	0xCE, 0x23, 0x58, 0x01,
	0x23, 0x59, 0x01, 0x33,
	0x5B, 0x00, 0x33, 0x5C,
	0x00, 0x00, 0x00, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd56[] = {
	0x02, 0x00, 0x29, 0xC0,
	0x00, 0xA0, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd57[] = {
	0x0F, 0x00, 0x29, 0xC0,
	0xCE, 0x38, 0x09, 0x03,
	0x5A, 0x00, 0x03, 0x00,
	0x38, 0x08, 0x03, 0x5B,
	0x00, 0x03, 0x00, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd58[] = {
	0x02, 0x00, 0x29, 0xC0,
	0x00, 0xB0, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd59[] = {
	0x0F, 0x00, 0x29, 0xC0,
	0xCE, 0x38, 0x07, 0x03,
	0x54, 0x00, 0x03, 0x00,
	0x38, 0x06, 0x03, 0x55,
	0x00, 0x03, 0x00, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd60[] = {
	0x02, 0x00, 0x29, 0xC0,
	0x00, 0xC0, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd61[] = {
	0x0F, 0x00, 0x29, 0xC0,
	0xCE, 0x38, 0x05, 0x03,
	0x56, 0x00, 0x03, 0x00,
	0x38, 0x04, 0x03, 0x57,
	0x00, 0x03, 0x00, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd62[] = {
	0x02, 0x00, 0x29, 0xC0,
	0x00, 0xD0, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd63[] = {
	0x0F, 0x00, 0x29, 0xC0,
	0xCE, 0x38, 0x03, 0x03,
	0x58, 0x00, 0x03, 0x00,
	0x38, 0x02, 0x03, 0x59,
	0x00, 0x03, 0x00, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd64[] = {
	0x02, 0x00, 0x29, 0xC0,
	0x00, 0xC0, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd65[] = {
	0x0B, 0x00, 0x29, 0xC0,
	0xCF, 0x3D, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x01,
	0x00, 0x00, 0x00, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd66[] = {
	0x02, 0x00, 0x29, 0xC0,
	0x00, 0x80, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd67[] = {
	0x0B, 0x00, 0x29, 0xC0,
	0xCB, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd68[] = {
	0x02, 0x00, 0x29, 0xC0,
	0x00, 0x90, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd69[] = {
	0x10, 0x00, 0x29, 0xC0,
	0xCB, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
};

static char otm8019a_fwvga_video_on_cmd70[] = {
	0x02, 0x00, 0x29, 0xC0,
	0x00, 0xA0, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd71[] = {
	0x10, 0x00, 0x29, 0xC0,
	0xCB, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
};

static char otm8019a_fwvga_video_on_cmd72[] = {
	0x02, 0x00, 0x29, 0xC0,
	0x00, 0xB0, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd73[] = {
	0x0B, 0x00, 0x29, 0xC0,
	0xCB, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd74[] = {
	0x02, 0x00, 0x29, 0xC0,
	0x00, 0xC0, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd75[] = {
	0x10, 0x00, 0x29, 0xC0,
	0xCB, 0x00, 0x00, 0x15,
	0x15, 0x15, 0x15, 0x15,
	0x00, 0x15, 0x15, 0x00,
	0x15, 0x15, 0x15, 0x15,
};

static char otm8019a_fwvga_video_on_cmd76[] = {
	0x02, 0x00, 0x29, 0xC0,
	0x00, 0xD0, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd77[] = {
	0x10, 0x00, 0x29, 0xC0,
	0xCB, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x15,
	0x15, 0x15, 0x15, 0x00,
	0x15, 0x15, 0x00, 0x15,
};

static char otm8019a_fwvga_video_on_cmd78[] = {
	0x02, 0x00, 0x29, 0xC0,
	0x00, 0xE0, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd79[] = {
	0x0B, 0x00, 0x29, 0xC0,
	0xCB, 0x15, 0x15, 0x15,
	0x15, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd80[] = {
	0x02, 0x00, 0x29, 0xC0,
	0x00, 0xF0, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd81[] = {
	0x0B, 0x00, 0x29, 0xC0,
	0xCB, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd82[] = {
	0x02, 0x00, 0x29, 0xC0,
	0x00, 0x80, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd83[] = {
	0x0B, 0x00, 0x29, 0xC0,
	0xCC, 0x00, 0x00, 0x02,
	0x0A, 0x0C, 0x0E, 0x10,
	0x00, 0x21, 0x22, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd84[] = {
	0x02, 0x00, 0x29, 0xC0,
	0x00, 0x90, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd85[] = {
	0x10, 0x00, 0x29, 0xC0,
	0xCC, 0x00, 0x06, 0x25,
	0x25, 0x08, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x07, 0x25, 0x25, 0x05,
};

static char otm8019a_fwvga_video_on_cmd86[] = {
	0x02, 0x00, 0x29, 0xC0,
	0x00, 0xA0, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd87[] = {
	0x10, 0x00, 0x29, 0xC0,
	0xCC, 0x00, 0x22, 0x21,
	0x00, 0x0f, 0x0d, 0x0b,
	0x09, 0x01, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
};

static char otm8019a_fwvga_video_on_cmd88[] = {
	0x02, 0x00, 0x29, 0xC0,
	0x00, 0xB0, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd89[] = {
	0x0B, 0x00, 0x29, 0xC0,
	0xCC, 0x00, 0x00, 0x05,
	0x09, 0x0F, 0x0D, 0x0B,
	0x00, 0x21, 0x22, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd90[] = {
	0x02, 0x00, 0x29, 0xC0,
	0x00, 0xC0, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd91[] = {
	0x10, 0x00, 0x29, 0xC0,
	0xCC, 0x00, 0x01, 0x25,
	0x25, 0x07, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x08, 0x25, 0x25, 0x02,
};

static char otm8019a_fwvga_video_on_cmd92[] = {
	0x02, 0x00, 0x29, 0xC0,
	0x00, 0xD0, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd93[] = {
	0x10, 0x00, 0x29, 0xC0,
	0xCC, 0x00, 0x22, 0x21,
	0x00, 0x0c, 0x0e, 0x10,
	0x0a, 0x06, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
};

static char otm8019a_fwvga_video_on_cmd94[] = {
	0x02, 0x00, 0x29, 0xC0,
	0x00, 0x00, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd95[] = {
	0x15, 0x00, 0x29, 0xC0,
	0xE1, 0x00, 0x07, 0x14,
	0x29, 0x3f, 0x52, 0x59,
	0x85, 0x72, 0x87, 0x81,
	0x70, 0x88, 0x74, 0x79,
	0x72, 0x6a, 0x61, 0x55,
	0x00, 0xFF, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd96[] = {
	0x02, 0x00, 0x29, 0xC0,
	0x00, 0x00, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd97[] = {
	0x15, 0x00, 0x29, 0xC0,
	0xE2, 0x00, 0x07, 0x14,
	0x29, 0x3f, 0x52, 0x59,
	0x85, 0x72, 0x87, 0x81,
	0x70, 0x88, 0x74, 0x79,
	0x72, 0x6a, 0x61, 0x55,
	0x00, 0xFF, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd98[] = {
	0x02, 0x00, 0x29, 0xC0,
	0x00, 0x00, 0xFF, 0xFF,
};

static char otm8019a_fwvga_video_on_cmd99[] = {
	0x04, 0x00, 0x29, 0xC0,
	0xff, 0xff, 0xff, 0xff,
};

static char otm8019a_fwvga_video_on_cmd100[] = {
	0x11, 0x00, 0x05, 0x80
};

static char otm8019a_fwvga_video_on_cmd101[] = {
	0x29, 0x00, 0x05, 0x80
};

static struct mipi_dsi_cmd otm8019a_fwvga_video_on_command[] = {
	{0x8, otm8019a_fwvga_video_on_cmd0, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd1, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd2, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd3, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd4, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd5, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd6, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd7, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd8, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd9, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd10, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd11, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd12, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd13, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd14, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd15, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd16, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd17, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd18, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd19, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd20, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd21, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd22, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd23, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd24, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd25, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd26, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd27, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd28, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd29, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd30, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd31, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd32, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd33, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd34, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd35, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd36, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd37, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd38, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd39, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd40, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd41, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd42, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd43, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd44, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd45, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd46, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd47, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd48, 0x00},
	{0x10, otm8019a_fwvga_video_on_cmd49, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd50, 0x00},
	{0xc, otm8019a_fwvga_video_on_cmd51, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd52, 0x00},
	{0xc, otm8019a_fwvga_video_on_cmd53, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd54, 0x00},
	{0x14, otm8019a_fwvga_video_on_cmd55, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd56, 0x00},
	{0x14, otm8019a_fwvga_video_on_cmd57, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd58, 0x00},
	{0x14, otm8019a_fwvga_video_on_cmd59, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd60, 0x00},
	{0x14, otm8019a_fwvga_video_on_cmd61, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd62, 0x00},
	{0x14, otm8019a_fwvga_video_on_cmd63, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd64, 0x00},
	{0x10, otm8019a_fwvga_video_on_cmd65, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd66, 0x00},
	{0x10, otm8019a_fwvga_video_on_cmd67, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd68, 0x00},
	{0x14, otm8019a_fwvga_video_on_cmd69, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd70, 0x00},
	{0x14, otm8019a_fwvga_video_on_cmd71, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd72, 0x00},
	{0x10, otm8019a_fwvga_video_on_cmd73, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd74, 0x00},
	{0x14, otm8019a_fwvga_video_on_cmd75, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd76, 0x00},
	{0x14, otm8019a_fwvga_video_on_cmd77, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd78, 0x00},
	{0x10, otm8019a_fwvga_video_on_cmd79, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd80, 0x00},
	{0x10, otm8019a_fwvga_video_on_cmd81, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd82, 0x00},
	{0x10, otm8019a_fwvga_video_on_cmd83, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd84, 0x00},
	{0x14, otm8019a_fwvga_video_on_cmd85, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd86, 0x00},
	{0x14, otm8019a_fwvga_video_on_cmd87, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd88, 0x00},
	{0x10, otm8019a_fwvga_video_on_cmd89, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd90, 0x00},
	{0x14, otm8019a_fwvga_video_on_cmd91, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd92, 0x00},
	{0x14, otm8019a_fwvga_video_on_cmd93, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd94, 0x00},
	{0x1c, otm8019a_fwvga_video_on_cmd95, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd96, 0x00},
	{0x1c, otm8019a_fwvga_video_on_cmd97, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd98, 0x00},
	{0x8, otm8019a_fwvga_video_on_cmd99, 0x00},
	{0x4, otm8019a_fwvga_video_on_cmd100, 0x78},
	{0x4, otm8019a_fwvga_video_on_cmd101, 0x28}
};

#define OTM8019A_FWVGA_VIDEO_ON_COMMAND 102


static char otm8019a_fwvga_videooff_cmd0[] = {
	0x28, 0x00, 0x05, 0x80
};

static char otm8019a_fwvga_videooff_cmd1[] = {
	0x10, 0x00, 0x05, 0x80
};

static struct mipi_dsi_cmd otm8019a_fwvga_video_off_command[] = {
	{0x4, otm8019a_fwvga_videooff_cmd0, 0x0A},
	{0x4, otm8019a_fwvga_videooff_cmd1, 0x78}
};

#define OTM8019A_FWVGA_VIDEO_OFF_COMMAND 2


static struct command_state otm8019a_fwvga_video_state = {
	0, 1
};

/*---------------------------------------------------------------------------*/
/* Command mode panel information                                            */
/*---------------------------------------------------------------------------*/
static struct commandpanel_info otm8019a_fwvga_video_command_panel = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/*---------------------------------------------------------------------------*/
/* Video mode panel information                                              */
/*---------------------------------------------------------------------------*/
static struct videopanel_info otm8019a_fwvga_video_video_panel = {
	1, 0, 0, 0, 1, 1, 2, 0, 0x9
};

/*---------------------------------------------------------------------------*/
/* Lane configuration                                                        */
/*---------------------------------------------------------------------------*/
static struct lane_configuration otm8019a_fwvga_video_lane_config = {
	2, 1, 1, 1, 0, 0, 0
};

/*---------------------------------------------------------------------------*/
/* Panel timing                                                              */
/*---------------------------------------------------------------------------*/
static const uint32_t otm8019a_fwvga_video_timings[] = {
	0x5F, 0x1D, 0x15, 0x00, 0x2E, 0x2D, 0x19, 0x1F, 0x24, 0x03, 0x04, 0x00
};

static struct panel_timing otm8019a_fwvga_video_timing_info = {
	0, 4, 0x20, 0x2A
};

/*---------------------------------------------------------------------------*/
/* Panel reset sequence                                                      */
/*---------------------------------------------------------------------------*/
static struct panel_reset_sequence otm8019a_fwvga_video_reset_seq = {
	{1, 0, 1, }, {20, 2, 20, }, 2
};

/*---------------------------------------------------------------------------*/
/* Backlight setting                                                         */
/*---------------------------------------------------------------------------*/
static struct backlight otm8019a_fwvga_video_backlight = {
	0, 1, 255, 0, 2, 0
};

#endif /*_PANEL_OTM8019A_FWVGA_VIDEO_H_*/
