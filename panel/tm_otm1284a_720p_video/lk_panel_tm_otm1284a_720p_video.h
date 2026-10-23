// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2026 FIXME
// Generated with linux-mdss-dsi-panel-driver-generator from vendor device tree:
//   Copyright (c) 2014, The Linux Foundation. All rights reserved. (FIXME)

#ifndef _PANEL_TM_OTM1284A_720P_VIDEO_H_
#define _PANEL_TM_OTM1284A_720P_VIDEO_H_

#include <mipi_dsi.h>
#include <panel_display.h>
#include <panel.h>
#include <string.h>

static struct panel_config tm_otm1284a_720p_video_panel_data = {
	.panel_node_id = "qcom,mdss_dsi_tm_otm1284a_720p_video",
	.panel_controller = "dsi:0:",
	.panel_compatible = "qcom,mdss-dsi-panel",
	.panel_type = 0,
	.panel_destination = "DISPLAY_1",
	/* .panel_orientation not supported yet */
	.panel_framerate = 60,
	.panel_lp11_init = 0,
	.panel_init_delay = 0,
};

static struct panel_resolution tm_otm1284a_720p_video_panel_res = {
	.panel_width = 720,
	.panel_height = 1280,
	.hfront_porch = 53,
	.hback_porch = 64,
	.hpulse_width = 4,
	.hsync_skew = 0,
	.vfront_porch = 16,
	.vback_porch = 16,
	.vpulse_width = 4,
	/* Borders not supported yet */
};

static struct color_info tm_otm1284a_720p_video_color = {
	.color_format = 24,
	.color_order = DSI_RGB_SWAP_RGB,
	.underflow_color = 0xff,
	/* Borders and pixel packing not supported yet */
};

static char tm_otm1284a_720p_video_on_cmd_0[] = {
	0x02, 0x00, 0x29, 0xc0, 0x00, 0x90, 0xff, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_1[] = {
	0x0d, 0x00, 0x29, 0xc0, 0xca, 0x9f, 0xff, 0x9f,
	0xff, 0x70, 0xff, 0x05, 0x03, 0x05, 0x03, 0x05,
	0x03, 0xff, 0xff, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_2[] = {
	0x02, 0x00, 0x29, 0xc0, 0x00, 0x00, 0xff, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_3[] = {
	0x02, 0x00, 0x29, 0xc0, 0xc6, 0x10, 0xff, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_4[] = {
	0x13, 0x00, 0x29, 0xc0, 0xc7, 0xa0, 0xab, 0xad,
	0xab, 0x99, 0xaa, 0xcb, 0xcd, 0xbb, 0x9c, 0x88,
	0x88, 0x67, 0x34, 0x33, 0x33, 0x33, 0x33, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_5[] = {
	0x02, 0x00, 0x29, 0xc0, 0x00, 0x00, 0xff, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_6[] = {
	0x02, 0x00, 0x29, 0xc0, 0xc6, 0x11, 0xff, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_7[] = {
	0x13, 0x00, 0x29, 0xc0, 0xc7, 0xa0, 0xba, 0xab,
	0xab, 0x99, 0xaa, 0xba, 0xcd, 0xab, 0x9c, 0x88,
	0x88, 0x67, 0x45, 0x44, 0x44, 0x33, 0x33, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_8[] = {
	0x02, 0x00, 0x29, 0xc0, 0x00, 0x00, 0xff, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_9[] = {
	0x02, 0x00, 0x29, 0xc0, 0xc6, 0x12, 0xff, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_10[] = {
	0x13, 0x00, 0x29, 0xc0, 0xc7, 0x90, 0xab, 0xab,
	0xab, 0x98, 0xb9, 0xb9, 0xcc, 0xba, 0xaa, 0x88,
	0x88, 0x68, 0x45, 0x44, 0x44, 0x44, 0x44, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_11[] = {
	0x02, 0x00, 0x29, 0xc0, 0x00, 0x00, 0xff, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_12[] = {
	0x02, 0x00, 0x29, 0xc0, 0xc6, 0x13, 0xff, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_13[] = {
	0x13, 0x00, 0x29, 0xc0, 0xc7, 0x90, 0xaa, 0xab,
	0x9a, 0x99, 0x9a, 0xaa, 0xbb, 0xab, 0xaa, 0x88,
	0x88, 0x78, 0x56, 0x45, 0x44, 0x44, 0x44, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_14[] = {
	0x02, 0x00, 0x29, 0xc0, 0x00, 0x00, 0xff, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_15[] = {
	0x02, 0x00, 0x29, 0xc0, 0xc6, 0x14, 0xff, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_16[] = {
	0x13, 0x00, 0x29, 0xc0, 0xc7, 0x90, 0x9a, 0xab,
	0x9a, 0x98, 0xa9, 0xa9, 0xbb, 0x9b, 0x9a, 0x88,
	0x88, 0x78, 0x56, 0x55, 0x55, 0x55, 0x45, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_17[] = {
	0x02, 0x00, 0x29, 0xc0, 0x00, 0x00, 0xff, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_18[] = {
	0x02, 0x00, 0x29, 0xc0, 0xc6, 0x15, 0xff, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_19[] = {
	0x13, 0x00, 0x29, 0xc0, 0xc7, 0x90, 0x99, 0x9b,
	0xaa, 0x98, 0x99, 0x99, 0xbb, 0xaa, 0x99, 0x88,
	0x88, 0x88, 0x67, 0x55, 0x55, 0x55, 0x55, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_20[] = {
	0x02, 0x00, 0x29, 0xc0, 0x00, 0x00, 0xff, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_21[] = {
	0x02, 0x00, 0x29, 0xc0, 0xc6, 0x16, 0xff, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_22[] = {
	0x13, 0x00, 0x29, 0xc0, 0xc7, 0x90, 0x99, 0xaa,
	0x99, 0x89, 0x99, 0x99, 0xab, 0xaa, 0x89, 0x88,
	0x88, 0x88, 0x67, 0x66, 0x66, 0x55, 0x55, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_23[] = {
	0x02, 0x00, 0x29, 0xc0, 0x00, 0x00, 0xff, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_24[] = {
	0x02, 0x00, 0x29, 0xc0, 0xc6, 0x17, 0xff, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_25[] = {
	0x13, 0x00, 0x29, 0xc0, 0xc7, 0x80, 0x99, 0xaa,
	0xa8, 0x88, 0x99, 0x99, 0xaa, 0xaa, 0x88, 0x88,
	0x88, 0x88, 0x67, 0x66, 0x66, 0x66, 0x66, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_26[] = {
	0x02, 0x00, 0x29, 0xc0, 0x00, 0x00, 0xff, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_27[] = {
	0x02, 0x00, 0x29, 0xc0, 0xc6, 0x18, 0xff, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_28[] = {
	0x13, 0x00, 0x29, 0xc0, 0xc7, 0x80, 0x99, 0xa9,
	0xa8, 0x88, 0x89, 0x99, 0x9a, 0x9a, 0x89, 0x88,
	0x88, 0x88, 0x78, 0x67, 0x66, 0x66, 0x66, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_29[] = {
	0x02, 0x00, 0x29, 0xc0, 0x00, 0x00, 0xff, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_30[] = {
	0x02, 0x00, 0x29, 0xc0, 0xc6, 0x19, 0xff, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_31[] = {
	0x13, 0x00, 0x29, 0xc0, 0xc7, 0x80, 0x89, 0x9a,
	0x98, 0x89, 0x98, 0x89, 0x9a, 0xa9, 0x79, 0x88,
	0x88, 0x88, 0x78, 0x77, 0x77, 0x66, 0x66, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_32[] = {
	0x02, 0x00, 0x29, 0xc0, 0x00, 0x00, 0xff, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_33[] = {
	0x02, 0x00, 0x29, 0xc0, 0xc6, 0x1a, 0xff, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_34[] = {
	0x13, 0x00, 0x29, 0xc0, 0xc7, 0x80, 0x98, 0x99,
	0x98, 0x89, 0x98, 0x98, 0x89, 0xa9, 0x89, 0x88,
	0x88, 0x88, 0x78, 0x77, 0x77, 0x77, 0x66, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_35[] = {
	0x02, 0x00, 0x29, 0xc0, 0x00, 0x00, 0xff, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_36[] = {
	0x02, 0x00, 0x29, 0xc0, 0xc6, 0x1b, 0xff, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_37[] = {
	0x13, 0x00, 0x29, 0xc0, 0xc7, 0x70, 0x99, 0xa8,
	0x97, 0x89, 0x88, 0x89, 0x99, 0x98, 0x89, 0x88,
	0x88, 0x88, 0x88, 0x77, 0x77, 0x77, 0x77, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_38[] = {
	0x02, 0x00, 0x29, 0xc0, 0x00, 0x00, 0xff, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_39[] = {
	0x02, 0x00, 0x29, 0xc0, 0xc6, 0x1c, 0xff, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_40[] = {
	0x13, 0x00, 0x29, 0xc0, 0xc7, 0x80, 0x98, 0xa8,
	0x97, 0x89, 0x88, 0x89, 0x89, 0x99, 0x89, 0x88,
	0x88, 0x88, 0x88, 0x77, 0x77, 0x77, 0x77, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_41[] = {
	0x02, 0x00, 0x29, 0xc0, 0x00, 0x00, 0xff, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_42[] = {
	0x02, 0x00, 0x29, 0xc0, 0xc6, 0x1d, 0xff, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_43[] = {
	0x13, 0x00, 0x29, 0xc0, 0xc7, 0x80, 0x88, 0x89,
	0x98, 0x88, 0x98, 0x88, 0x89, 0x99, 0x88, 0x88,
	0x88, 0x88, 0x88, 0x88, 0x78, 0x77, 0x77, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_44[] = {
	0x02, 0x00, 0x29, 0xc0, 0x00, 0x00, 0xff, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_45[] = {
	0x02, 0x00, 0x29, 0xc0, 0xc6, 0x1e, 0xff, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_46[] = {
	0x13, 0x00, 0x29, 0xc0, 0xc7, 0x80, 0x88, 0x98,
	0x97, 0x88, 0x98, 0x88, 0x89, 0x98, 0x88, 0x88,
	0x88, 0x88, 0x88, 0x88, 0x88, 0x78, 0x77, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_47[] = {
	0x02, 0x00, 0x29, 0xc0, 0x00, 0x00, 0xff, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_48[] = {
	0x02, 0x00, 0x29, 0xc0, 0xc6, 0x1f, 0xff, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_49[] = {
	0x13, 0x00, 0x29, 0xc0, 0xc7, 0x80, 0x88, 0x88,
	0x98, 0x87, 0x98, 0x88, 0x88, 0x88, 0x89, 0x88,
	0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x78, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_50[] = {
	0x02, 0x00, 0x29, 0xc0, 0x00, 0x00, 0xff, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_51[] = {
	0x02, 0x00, 0x29, 0xc0, 0xc6, 0x00, 0xff, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_52[] = {
	0x02, 0x00, 0x29, 0xc0, 0x00, 0xb3, 0xff, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_53[] = {
	0x02, 0x00, 0x29, 0xc0, 0xc5, 0x84, 0xff, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_54[] = {
	0x02, 0x00, 0x29, 0xc0, 0x00, 0xb1, 0xff, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_55[] = {
	0x02, 0x00, 0x29, 0xc0, 0xc6, 0x02, 0xff, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_56[] = {
	0x02, 0x00, 0x29, 0xc0, 0x00, 0xb4, 0xff, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_57[] = {
	0x02, 0x00, 0x29, 0xc0, 0xc6, 0x10, 0xff, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_58[] = {
	0x02, 0x00, 0x29, 0xc0, 0x00, 0x81, 0xff, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_59[] = {
	0x02, 0x00, 0x29, 0xc0, 0xc1, 0x66, 0xff, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_60[] = {
	0x02, 0x00, 0x29, 0xc0, 0x00, 0x83, 0xff, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_61[] = {
	0x02, 0x00, 0x29, 0xc0, 0xc1, 0xb0, 0xff, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_62[] = {
	0x5e, 0x0c, 0x15, 0x80
};
static char tm_otm1284a_720p_video_on_cmd_63[] = {
	0x02, 0x00, 0x29, 0xc0, 0x51, 0x00, 0xff, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_64[] = {
	0x02, 0x00, 0x29, 0xc0, 0x53, 0x24, 0xff, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_65[] = {
	0x02, 0x00, 0x29, 0xc0, 0x55, 0x00, 0xff, 0xff
};
static char tm_otm1284a_720p_video_on_cmd_66[] = {
	0x11, 0x00, 0x05, 0x80
};
static char tm_otm1284a_720p_video_on_cmd_67[] = {
	0x29, 0x00, 0x05, 0x80
};

static struct mipi_dsi_cmd tm_otm1284a_720p_video_on_command[] = {
	{ sizeof(tm_otm1284a_720p_video_on_cmd_0), tm_otm1284a_720p_video_on_cmd_0, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_1), tm_otm1284a_720p_video_on_cmd_1, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_2), tm_otm1284a_720p_video_on_cmd_2, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_3), tm_otm1284a_720p_video_on_cmd_3, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_4), tm_otm1284a_720p_video_on_cmd_4, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_5), tm_otm1284a_720p_video_on_cmd_5, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_6), tm_otm1284a_720p_video_on_cmd_6, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_7), tm_otm1284a_720p_video_on_cmd_7, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_8), tm_otm1284a_720p_video_on_cmd_8, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_9), tm_otm1284a_720p_video_on_cmd_9, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_10), tm_otm1284a_720p_video_on_cmd_10, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_11), tm_otm1284a_720p_video_on_cmd_11, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_12), tm_otm1284a_720p_video_on_cmd_12, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_13), tm_otm1284a_720p_video_on_cmd_13, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_14), tm_otm1284a_720p_video_on_cmd_14, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_15), tm_otm1284a_720p_video_on_cmd_15, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_16), tm_otm1284a_720p_video_on_cmd_16, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_17), tm_otm1284a_720p_video_on_cmd_17, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_18), tm_otm1284a_720p_video_on_cmd_18, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_19), tm_otm1284a_720p_video_on_cmd_19, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_20), tm_otm1284a_720p_video_on_cmd_20, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_21), tm_otm1284a_720p_video_on_cmd_21, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_22), tm_otm1284a_720p_video_on_cmd_22, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_23), tm_otm1284a_720p_video_on_cmd_23, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_24), tm_otm1284a_720p_video_on_cmd_24, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_25), tm_otm1284a_720p_video_on_cmd_25, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_26), tm_otm1284a_720p_video_on_cmd_26, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_27), tm_otm1284a_720p_video_on_cmd_27, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_28), tm_otm1284a_720p_video_on_cmd_28, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_29), tm_otm1284a_720p_video_on_cmd_29, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_30), tm_otm1284a_720p_video_on_cmd_30, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_31), tm_otm1284a_720p_video_on_cmd_31, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_32), tm_otm1284a_720p_video_on_cmd_32, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_33), tm_otm1284a_720p_video_on_cmd_33, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_34), tm_otm1284a_720p_video_on_cmd_34, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_35), tm_otm1284a_720p_video_on_cmd_35, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_36), tm_otm1284a_720p_video_on_cmd_36, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_37), tm_otm1284a_720p_video_on_cmd_37, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_38), tm_otm1284a_720p_video_on_cmd_38, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_39), tm_otm1284a_720p_video_on_cmd_39, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_40), tm_otm1284a_720p_video_on_cmd_40, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_41), tm_otm1284a_720p_video_on_cmd_41, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_42), tm_otm1284a_720p_video_on_cmd_42, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_43), tm_otm1284a_720p_video_on_cmd_43, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_44), tm_otm1284a_720p_video_on_cmd_44, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_45), tm_otm1284a_720p_video_on_cmd_45, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_46), tm_otm1284a_720p_video_on_cmd_46, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_47), tm_otm1284a_720p_video_on_cmd_47, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_48), tm_otm1284a_720p_video_on_cmd_48, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_49), tm_otm1284a_720p_video_on_cmd_49, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_50), tm_otm1284a_720p_video_on_cmd_50, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_51), tm_otm1284a_720p_video_on_cmd_51, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_52), tm_otm1284a_720p_video_on_cmd_52, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_53), tm_otm1284a_720p_video_on_cmd_53, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_54), tm_otm1284a_720p_video_on_cmd_54, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_55), tm_otm1284a_720p_video_on_cmd_55, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_56), tm_otm1284a_720p_video_on_cmd_56, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_57), tm_otm1284a_720p_video_on_cmd_57, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_58), tm_otm1284a_720p_video_on_cmd_58, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_59), tm_otm1284a_720p_video_on_cmd_59, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_60), tm_otm1284a_720p_video_on_cmd_60, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_61), tm_otm1284a_720p_video_on_cmd_61, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_62), tm_otm1284a_720p_video_on_cmd_62, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_63), tm_otm1284a_720p_video_on_cmd_63, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_64), tm_otm1284a_720p_video_on_cmd_64, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_65), tm_otm1284a_720p_video_on_cmd_65, 0 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_66), tm_otm1284a_720p_video_on_cmd_66, 200 },
	{ sizeof(tm_otm1284a_720p_video_on_cmd_67), tm_otm1284a_720p_video_on_cmd_67, 0 },
};

static char tm_otm1284a_720p_video_off_cmd_0[] = {
	0x28, 0x00, 0x05, 0x80
};
static char tm_otm1284a_720p_video_off_cmd_1[] = {
	0x10, 0x00, 0x05, 0x80
};

static struct mipi_dsi_cmd tm_otm1284a_720p_video_off_command[] = {
	{ sizeof(tm_otm1284a_720p_video_off_cmd_0), tm_otm1284a_720p_video_off_cmd_0, 50 },
	{ sizeof(tm_otm1284a_720p_video_off_cmd_1), tm_otm1284a_720p_video_off_cmd_1, 120 },
};

static struct command_state tm_otm1284a_720p_video_state = {
	.oncommand_state = 0,
	.offcommand_state = 1,
};

static struct commandpanel_info tm_otm1284a_720p_video_command_panel = {
	/* Unused, this is a video mode panel */
};

static struct videopanel_info tm_otm1284a_720p_video_video_panel = {
	.hsync_pulse = 1,
	.hfp_power_mode = 0,
	.hbp_power_mode = 0,
	.hsa_power_mode = 0,
	.bllp_eof_power_mode = 1,
	.bllp_power_mode = 1,
	.traffic_mode = 2,
	/* This is bllp_eof_power_mode and bllp_power_mode combined */
	.bllp_eof_power = 1 << 3 | 1 << 0,
};

static struct lane_configuration tm_otm1284a_720p_video_lane_config = {
	.dsi_lanes = 4,
	.dsi_lanemap = 0,
	.lane0_state = 1,
	.lane1_state = 1,
	.lane2_state = 1,
	.lane3_state = 1,
	.force_clk_lane_hs = 0,
};

static const uint32_t tm_otm1284a_720p_video_timings[] = {
	0x80, 0x20, 0x1a, 0x00, 0x3c, 0x38, 0x1a, 0x20, 0x13, 0x03, 0x04, 0x00
};

static struct panel_timing tm_otm1284a_720p_video_timing_info = {
	.tclk_post = 0x04,
	.tclk_pre = 0x1b,
};

static struct panel_reset_sequence tm_otm1284a_720p_video_reset_seq = {
	.pin_state = { 1, 0, 1 },
	.sleep = { 10, 10, 10 },
	.pin_direction = 2,
};

static struct backlight tm_otm1284a_720p_video_backlight = {
	.bl_interface_type = BL_DCS,
	.bl_min_level = 1,
	.bl_max_level = 255,
};

static inline void panel_tm_otm1284a_720p_video_select(struct panel_struct *panel,
						       struct msm_panel_info *pinfo,
						       struct mdss_dsi_phy_ctrl *phy_db)
{
	panel->paneldata = &tm_otm1284a_720p_video_panel_data;
	panel->panelres = &tm_otm1284a_720p_video_panel_res;
	panel->color = &tm_otm1284a_720p_video_color;
	panel->videopanel = &tm_otm1284a_720p_video_video_panel;
	panel->commandpanel = &tm_otm1284a_720p_video_command_panel;
	panel->state = &tm_otm1284a_720p_video_state;
	panel->laneconfig = &tm_otm1284a_720p_video_lane_config;
	panel->paneltiminginfo = &tm_otm1284a_720p_video_timing_info;
	panel->panelresetseq = &tm_otm1284a_720p_video_reset_seq;
	panel->backlightinfo = &tm_otm1284a_720p_video_backlight;
	pinfo->mipi.panel_on_cmds = tm_otm1284a_720p_video_on_command;
	pinfo->mipi.panel_off_cmds = tm_otm1284a_720p_video_off_command;
	pinfo->mipi.num_of_panel_on_cmds = ARRAY_SIZE(tm_otm1284a_720p_video_on_command);
	pinfo->mipi.num_of_panel_off_cmds = ARRAY_SIZE(tm_otm1284a_720p_video_off_command);
	memcpy(phy_db->timing, tm_otm1284a_720p_video_timings, TIMING_SIZE);
	phy_db->regulator_mode = DSI_PHY_REGULATOR_LDO_MODE;
}

#endif /* _PANEL_TM_OTM1284A_720P_VIDEO_H_ */
