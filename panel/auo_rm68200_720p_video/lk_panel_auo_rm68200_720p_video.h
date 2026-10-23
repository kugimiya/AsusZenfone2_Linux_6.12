// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2026 FIXME
// Generated with linux-mdss-dsi-panel-driver-generator from vendor device tree:
//   Copyright (c) 2014, The Linux Foundation. All rights reserved. (FIXME)

#ifndef _PANEL_AUO_RM68200_720P_VIDEO_H_
#define _PANEL_AUO_RM68200_720P_VIDEO_H_

#include <mipi_dsi.h>
#include <panel_display.h>
#include <panel.h>
#include <string.h>

static struct panel_config auo_rm68200_720p_video_panel_data = {
	.panel_node_id = "qcom,mdss_dsi_auo_rm68200_720p_video",
	.panel_controller = "dsi:0:",
	.panel_compatible = "qcom,mdss-dsi-panel",
	.panel_type = 0,
	.panel_destination = "DISPLAY_1",
	/* .panel_orientation not supported yet */
	.panel_framerate = 60,
	.panel_lp11_init = 0,
	.panel_init_delay = 0,
};

static struct panel_resolution auo_rm68200_720p_video_panel_res = {
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

static struct color_info auo_rm68200_720p_video_color = {
	.color_format = 24,
	.color_order = DSI_RGB_SWAP_RGB,
	.underflow_color = 0xff,
	/* Borders and pixel packing not supported yet */
};

static char auo_rm68200_720p_video_on_cmd_0[] = {
	0xfe, 0x04, 0x15, 0x80
};
static char auo_rm68200_720p_video_on_cmd_1[] = {
	0x5f, 0x0a, 0x15, 0x80
};
static char auo_rm68200_720p_video_on_cmd_2[] = {
	0x60, 0x09, 0x15, 0x80
};
static char auo_rm68200_720p_video_on_cmd_3[] = {
	0x61, 0x11, 0x15, 0x80
};
static char auo_rm68200_720p_video_on_cmd_4[] = {
	0x62, 0x18, 0x15, 0x80
};
static char auo_rm68200_720p_video_on_cmd_5[] = {
	0x63, 0x09, 0x15, 0x80
};
static char auo_rm68200_720p_video_on_cmd_6[] = {
	0x64, 0x03, 0x15, 0x80
};
static char auo_rm68200_720p_video_on_cmd_7[] = {
	0x65, 0x0f, 0x15, 0x80
};
static char auo_rm68200_720p_video_on_cmd_8[] = {
	0x66, 0x10, 0x15, 0x80
};
static char auo_rm68200_720p_video_on_cmd_9[] = {
	0x67, 0x0d, 0x15, 0x80
};
static char auo_rm68200_720p_video_on_cmd_10[] = {
	0x68, 0x15, 0x15, 0x80
};
static char auo_rm68200_720p_video_on_cmd_11[] = {
	0x69, 0x0b, 0x15, 0x80
};
static char auo_rm68200_720p_video_on_cmd_12[] = {
	0x6a, 0x0d, 0x15, 0x80
};
static char auo_rm68200_720p_video_on_cmd_13[] = {
	0x6b, 0x07, 0x15, 0x80
};
static char auo_rm68200_720p_video_on_cmd_14[] = {
	0x6c, 0x0f, 0x15, 0x80
};
static char auo_rm68200_720p_video_on_cmd_15[] = {
	0x6d, 0x11, 0x15, 0x80
};
static char auo_rm68200_720p_video_on_cmd_16[] = {
	0x6e, 0x0e, 0x15, 0x80
};
static char auo_rm68200_720p_video_on_cmd_17[] = {
	0x6f, 0x09, 0x15, 0x80
};
static char auo_rm68200_720p_video_on_cmd_18[] = {
	0x70, 0x09, 0x15, 0x80
};
static char auo_rm68200_720p_video_on_cmd_19[] = {
	0x71, 0x11, 0x15, 0x80
};
static char auo_rm68200_720p_video_on_cmd_20[] = {
	0x72, 0x18, 0x15, 0x80
};
static char auo_rm68200_720p_video_on_cmd_21[] = {
	0x73, 0x09, 0x15, 0x80
};
static char auo_rm68200_720p_video_on_cmd_22[] = {
	0x74, 0x03, 0x15, 0x80
};
static char auo_rm68200_720p_video_on_cmd_23[] = {
	0x75, 0x0f, 0x15, 0x80
};
static char auo_rm68200_720p_video_on_cmd_24[] = {
	0x76, 0x10, 0x15, 0x80
};
static char auo_rm68200_720p_video_on_cmd_25[] = {
	0x77, 0x0d, 0x15, 0x80
};
static char auo_rm68200_720p_video_on_cmd_26[] = {
	0x78, 0x15, 0x15, 0x80
};
static char auo_rm68200_720p_video_on_cmd_27[] = {
	0x79, 0x0b, 0x15, 0x80
};
static char auo_rm68200_720p_video_on_cmd_28[] = {
	0x7a, 0x0d, 0x15, 0x80
};
static char auo_rm68200_720p_video_on_cmd_29[] = {
	0x7b, 0x07, 0x15, 0x80
};
static char auo_rm68200_720p_video_on_cmd_30[] = {
	0x7c, 0x0f, 0x15, 0x80
};
static char auo_rm68200_720p_video_on_cmd_31[] = {
	0x7d, 0x11, 0x15, 0x80
};
static char auo_rm68200_720p_video_on_cmd_32[] = {
	0x7e, 0x0e, 0x15, 0x80
};
static char auo_rm68200_720p_video_on_cmd_33[] = {
	0x7f, 0x09, 0x15, 0x80
};
static char auo_rm68200_720p_video_on_cmd_34[] = {
	0x1c, 0x33, 0x15, 0x80
};
static char auo_rm68200_720p_video_on_cmd_35[] = {
	0x1d, 0x44, 0x15, 0x80
};
static char auo_rm68200_720p_video_on_cmd_36[] = {
	0x1e, 0x55, 0x15, 0x80
};
static char auo_rm68200_720p_video_on_cmd_37[] = {
	0x1f, 0x67, 0x15, 0x80
};
static char auo_rm68200_720p_video_on_cmd_38[] = {
	0x20, 0x89, 0x15, 0x80
};
static char auo_rm68200_720p_video_on_cmd_39[] = {
	0x21, 0xab, 0x15, 0x80
};
static char auo_rm68200_720p_video_on_cmd_40[] = {
	0x0a, 0x62, 0x15, 0x80
};
static char auo_rm68200_720p_video_on_cmd_41[] = {
	0x15, 0xfe, 0x15, 0x80
};
static char auo_rm68200_720p_video_on_cmd_42[] = {
	0x27, 0x5b, 0x15, 0x80
};
static char auo_rm68200_720p_video_on_cmd_43[] = {
	0xfe, 0x00, 0x15, 0x80
};
static char auo_rm68200_720p_video_on_cmd_44[] = {
	0x5e, 0x0c, 0x15, 0x80
};
static char auo_rm68200_720p_video_on_cmd_45[] = {
	0x51, 0x00, 0x15, 0x80
};
static char auo_rm68200_720p_video_on_cmd_46[] = {
	0x53, 0x24, 0x15, 0x80
};
static char auo_rm68200_720p_video_on_cmd_47[] = {
	0x55, 0x00, 0x15, 0x80
};
static char auo_rm68200_720p_video_on_cmd_48[] = {
	0x11, 0x00, 0x05, 0x80
};
static char auo_rm68200_720p_video_on_cmd_49[] = {
	0x29, 0x00, 0x05, 0x80
};

static struct mipi_dsi_cmd auo_rm68200_720p_video_on_command[] = {
	{ sizeof(auo_rm68200_720p_video_on_cmd_0), auo_rm68200_720p_video_on_cmd_0, 0 },
	{ sizeof(auo_rm68200_720p_video_on_cmd_1), auo_rm68200_720p_video_on_cmd_1, 0 },
	{ sizeof(auo_rm68200_720p_video_on_cmd_2), auo_rm68200_720p_video_on_cmd_2, 0 },
	{ sizeof(auo_rm68200_720p_video_on_cmd_3), auo_rm68200_720p_video_on_cmd_3, 0 },
	{ sizeof(auo_rm68200_720p_video_on_cmd_4), auo_rm68200_720p_video_on_cmd_4, 0 },
	{ sizeof(auo_rm68200_720p_video_on_cmd_5), auo_rm68200_720p_video_on_cmd_5, 0 },
	{ sizeof(auo_rm68200_720p_video_on_cmd_6), auo_rm68200_720p_video_on_cmd_6, 0 },
	{ sizeof(auo_rm68200_720p_video_on_cmd_7), auo_rm68200_720p_video_on_cmd_7, 0 },
	{ sizeof(auo_rm68200_720p_video_on_cmd_8), auo_rm68200_720p_video_on_cmd_8, 0 },
	{ sizeof(auo_rm68200_720p_video_on_cmd_9), auo_rm68200_720p_video_on_cmd_9, 0 },
	{ sizeof(auo_rm68200_720p_video_on_cmd_10), auo_rm68200_720p_video_on_cmd_10, 0 },
	{ sizeof(auo_rm68200_720p_video_on_cmd_11), auo_rm68200_720p_video_on_cmd_11, 0 },
	{ sizeof(auo_rm68200_720p_video_on_cmd_12), auo_rm68200_720p_video_on_cmd_12, 0 },
	{ sizeof(auo_rm68200_720p_video_on_cmd_13), auo_rm68200_720p_video_on_cmd_13, 0 },
	{ sizeof(auo_rm68200_720p_video_on_cmd_14), auo_rm68200_720p_video_on_cmd_14, 0 },
	{ sizeof(auo_rm68200_720p_video_on_cmd_15), auo_rm68200_720p_video_on_cmd_15, 0 },
	{ sizeof(auo_rm68200_720p_video_on_cmd_16), auo_rm68200_720p_video_on_cmd_16, 0 },
	{ sizeof(auo_rm68200_720p_video_on_cmd_17), auo_rm68200_720p_video_on_cmd_17, 0 },
	{ sizeof(auo_rm68200_720p_video_on_cmd_18), auo_rm68200_720p_video_on_cmd_18, 0 },
	{ sizeof(auo_rm68200_720p_video_on_cmd_19), auo_rm68200_720p_video_on_cmd_19, 0 },
	{ sizeof(auo_rm68200_720p_video_on_cmd_20), auo_rm68200_720p_video_on_cmd_20, 0 },
	{ sizeof(auo_rm68200_720p_video_on_cmd_21), auo_rm68200_720p_video_on_cmd_21, 0 },
	{ sizeof(auo_rm68200_720p_video_on_cmd_22), auo_rm68200_720p_video_on_cmd_22, 0 },
	{ sizeof(auo_rm68200_720p_video_on_cmd_23), auo_rm68200_720p_video_on_cmd_23, 0 },
	{ sizeof(auo_rm68200_720p_video_on_cmd_24), auo_rm68200_720p_video_on_cmd_24, 0 },
	{ sizeof(auo_rm68200_720p_video_on_cmd_25), auo_rm68200_720p_video_on_cmd_25, 0 },
	{ sizeof(auo_rm68200_720p_video_on_cmd_26), auo_rm68200_720p_video_on_cmd_26, 0 },
	{ sizeof(auo_rm68200_720p_video_on_cmd_27), auo_rm68200_720p_video_on_cmd_27, 0 },
	{ sizeof(auo_rm68200_720p_video_on_cmd_28), auo_rm68200_720p_video_on_cmd_28, 0 },
	{ sizeof(auo_rm68200_720p_video_on_cmd_29), auo_rm68200_720p_video_on_cmd_29, 0 },
	{ sizeof(auo_rm68200_720p_video_on_cmd_30), auo_rm68200_720p_video_on_cmd_30, 0 },
	{ sizeof(auo_rm68200_720p_video_on_cmd_31), auo_rm68200_720p_video_on_cmd_31, 0 },
	{ sizeof(auo_rm68200_720p_video_on_cmd_32), auo_rm68200_720p_video_on_cmd_32, 0 },
	{ sizeof(auo_rm68200_720p_video_on_cmd_33), auo_rm68200_720p_video_on_cmd_33, 0 },
	{ sizeof(auo_rm68200_720p_video_on_cmd_34), auo_rm68200_720p_video_on_cmd_34, 0 },
	{ sizeof(auo_rm68200_720p_video_on_cmd_35), auo_rm68200_720p_video_on_cmd_35, 0 },
	{ sizeof(auo_rm68200_720p_video_on_cmd_36), auo_rm68200_720p_video_on_cmd_36, 0 },
	{ sizeof(auo_rm68200_720p_video_on_cmd_37), auo_rm68200_720p_video_on_cmd_37, 0 },
	{ sizeof(auo_rm68200_720p_video_on_cmd_38), auo_rm68200_720p_video_on_cmd_38, 0 },
	{ sizeof(auo_rm68200_720p_video_on_cmd_39), auo_rm68200_720p_video_on_cmd_39, 0 },
	{ sizeof(auo_rm68200_720p_video_on_cmd_40), auo_rm68200_720p_video_on_cmd_40, 0 },
	{ sizeof(auo_rm68200_720p_video_on_cmd_41), auo_rm68200_720p_video_on_cmd_41, 0 },
	{ sizeof(auo_rm68200_720p_video_on_cmd_42), auo_rm68200_720p_video_on_cmd_42, 0 },
	{ sizeof(auo_rm68200_720p_video_on_cmd_43), auo_rm68200_720p_video_on_cmd_43, 0 },
	{ sizeof(auo_rm68200_720p_video_on_cmd_44), auo_rm68200_720p_video_on_cmd_44, 0 },
	{ sizeof(auo_rm68200_720p_video_on_cmd_45), auo_rm68200_720p_video_on_cmd_45, 0 },
	{ sizeof(auo_rm68200_720p_video_on_cmd_46), auo_rm68200_720p_video_on_cmd_46, 0 },
	{ sizeof(auo_rm68200_720p_video_on_cmd_47), auo_rm68200_720p_video_on_cmd_47, 0 },
	{ sizeof(auo_rm68200_720p_video_on_cmd_48), auo_rm68200_720p_video_on_cmd_48, 150 },
	{ sizeof(auo_rm68200_720p_video_on_cmd_49), auo_rm68200_720p_video_on_cmd_49, 0 },
};

static char auo_rm68200_720p_video_off_cmd_0[] = {
	0x28, 0x00, 0x15, 0x80
};
static char auo_rm68200_720p_video_off_cmd_1[] = {
	0x10, 0x00, 0x15, 0x80
};

static struct mipi_dsi_cmd auo_rm68200_720p_video_off_command[] = {
	{ sizeof(auo_rm68200_720p_video_off_cmd_0), auo_rm68200_720p_video_off_cmd_0, 50 },
	{ sizeof(auo_rm68200_720p_video_off_cmd_1), auo_rm68200_720p_video_off_cmd_1, 120 },
};

static struct command_state auo_rm68200_720p_video_state = {
	.oncommand_state = 0,
	.offcommand_state = 1,
};

static struct commandpanel_info auo_rm68200_720p_video_command_panel = {
	/* Unused, this is a video mode panel */
};

static struct videopanel_info auo_rm68200_720p_video_video_panel = {
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

static struct lane_configuration auo_rm68200_720p_video_lane_config = {
	.dsi_lanes = 4,
	.dsi_lanemap = 0,
	.lane0_state = 1,
	.lane1_state = 1,
	.lane2_state = 1,
	.lane3_state = 1,
	.force_clk_lane_hs = 0,
};

static const uint32_t auo_rm68200_720p_video_timings[] = {
	0x75, 0x18, 0x10, 0x00, 0x3a, 0x3e, 0x14, 0x1a, 0x13, 0x03, 0x04, 0x00
};

static struct panel_timing auo_rm68200_720p_video_timing_info = {
	.tclk_post = 0x2c,
	.tclk_pre = 0x20,
};

static struct panel_reset_sequence auo_rm68200_720p_video_reset_seq = {
	.pin_state = { 1, 0, 1 },
	.sleep = { 10, 10, 10 },
	.pin_direction = 2,
};

static struct backlight auo_rm68200_720p_video_backlight = {
	.bl_interface_type = BL_DCS,
	.bl_min_level = 1,
	.bl_max_level = 255,
};

static inline void panel_auo_rm68200_720p_video_select(struct panel_struct *panel,
						       struct msm_panel_info *pinfo,
						       struct mdss_dsi_phy_ctrl *phy_db)
{
	panel->paneldata = &auo_rm68200_720p_video_panel_data;
	panel->panelres = &auo_rm68200_720p_video_panel_res;
	panel->color = &auo_rm68200_720p_video_color;
	panel->videopanel = &auo_rm68200_720p_video_video_panel;
	panel->commandpanel = &auo_rm68200_720p_video_command_panel;
	panel->state = &auo_rm68200_720p_video_state;
	panel->laneconfig = &auo_rm68200_720p_video_lane_config;
	panel->paneltiminginfo = &auo_rm68200_720p_video_timing_info;
	panel->panelresetseq = &auo_rm68200_720p_video_reset_seq;
	panel->backlightinfo = &auo_rm68200_720p_video_backlight;
	pinfo->mipi.panel_on_cmds = auo_rm68200_720p_video_on_command;
	pinfo->mipi.panel_off_cmds = auo_rm68200_720p_video_off_command;
	pinfo->mipi.num_of_panel_on_cmds = ARRAY_SIZE(auo_rm68200_720p_video_on_command);
	pinfo->mipi.num_of_panel_off_cmds = ARRAY_SIZE(auo_rm68200_720p_video_off_command);
	memcpy(phy_db->timing, auo_rm68200_720p_video_timings, TIMING_SIZE);
	phy_db->regulator_mode = DSI_PHY_REGULATOR_LDO_MODE;
}

#endif /* _PANEL_AUO_RM68200_720P_VIDEO_H_ */
