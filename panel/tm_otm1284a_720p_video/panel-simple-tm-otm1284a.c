// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2013, The Linux Foundation. All rights reserved.

static const struct drm_display_mode tm_otm1284a_mode = {
	.clock = (720 + 53 + 4 + 64) * (1280 + 16 + 4 + 16) * 60 / 1000,
	.hdisplay = 720,
	.hsync_start = 720 + 53,
	.hsync_end = 720 + 53 + 4,
	.htotal = 720 + 53 + 4 + 64,
	.vdisplay = 1280,
	.vsync_start = 1280 + 16,
	.vsync_end = 1280 + 16 + 4,
	.vtotal = 1280 + 16 + 4 + 16,
	.width_mm = 62,
	.height_mm = 110,
	.type = DRM_MODE_TYPE_DRIVER,
};

static const struct panel_desc_dsi tm_otm1284a = {
	.desc = {
		.modes = &tm_otm1284a_mode,
		.num_modes = 1,
		.bpc = 8,
		.size = {
			.width = 62,
			.height = 110,
		},
		.connector_type = DRM_MODE_CONNECTOR_DSI,
	},
	.flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BURST |
		 MIPI_DSI_MODE_VIDEO_HSE | MIPI_DSI_MODE_NO_EOT_PACKET |
		 MIPI_DSI_CLOCK_NON_CONTINUOUS,
	.format = MIPI_DSI_FMT_RGB888,
	.lanes = 4,
};
