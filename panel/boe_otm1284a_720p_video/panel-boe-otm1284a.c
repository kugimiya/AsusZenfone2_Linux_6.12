// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2026 FIXME
// Generated with linux-mdss-dsi-panel-driver-generator from vendor device tree:
//   Copyright (c) 2013, The Linux Foundation. All rights reserved. (FIXME)

#include <linux/backlight.h>
#include <linux/delay.h>
#include <linux/device-id/of.h>
#include <linux/gpio/consumer.h>
#include <linux/module.h>
#include <linux/regulator/consumer.h>

#include <video/mipi_display.h>

#include <drm/drm_mipi_dsi.h>
#include <drm/drm_modes.h>
#include <drm/drm_panel.h>
#include <drm/drm_probe_helper.h>

struct boe_otm1284a {
	struct drm_panel panel;
	struct mipi_dsi_device *dsi;
	struct regulator_bulk_data *supplies;
	struct gpio_desc *reset_gpio;
};

static const struct regulator_bulk_data boe_otm1284a_supplies[] = {
	{ .supply = "vdd" },
	{ .supply = "vddio" },
};

static inline struct boe_otm1284a *to_boe_otm1284a(struct drm_panel *panel)
{
	return container_of_const(panel, struct boe_otm1284a, panel);
}

static void boe_otm1284a_reset(struct boe_otm1284a *ctx)
{
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	usleep_range(10000, 11000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	usleep_range(10000, 11000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	usleep_range(10000, 11000);
}

static int boe_otm1284a_on(struct boe_otm1284a *ctx)
{
	struct mipi_dsi_multi_context dsi_ctx = { .dsi = ctx->dsi };

	ctx->dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xff, 0x12, 0x84, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x80);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xff, 0x12, 0x84);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x80);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xb0, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x81);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xb0, 0x11);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x82);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xb0, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x83);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xb0, 0x41);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x84);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xb0, 0x06);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x91);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xb0, 0x9a);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x92);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xff, 0x30, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x80);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc0,
					 0x00, 0x64, 0x00, 0x0f, 0x11, 0x00,
					 0x64, 0x0f, 0x11);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x90);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc0,
					 0x00, 0x5f, 0x00, 0x01, 0x00, 0x04);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xa4);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc0, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xb3);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc0, 0x00, 0x50);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x81);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc1, 0x55);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x90);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xf5,
					 0x02, 0x11, 0x02, 0x15);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x90);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc5, 0x50);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x94);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc5, 0x66);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xb2);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xf5, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xb4);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xf5, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xb6);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xf5, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xb8);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xf5, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xb4);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc5, 0xcc);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xa0);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc4,
					 0x05, 0x10, 0x06, 0x02, 0x05, 0x15,
					 0x10, 0x05, 0x10, 0x07, 0x02, 0x05,
					 0x15, 0x10);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xb0);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc4, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x91);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc5, 0x19, 0x52);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xd8, 0xc7, 0xc7);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xb3);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc5, 0x84);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xbb);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc5, 0x8a);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xb2);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc5, 0x40);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x81);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc4, 0x82, 0x0a);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xc6);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xb0, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xe1,
					 0x0c, 0x10, 0x1d, 0x22, 0x38, 0x3e,
					 0x3e, 0x65, 0x53, 0x6d, 0x96, 0x80,
					 0x8e, 0x67, 0x64, 0x61, 0x4e, 0x25,
					 0x1b, 0x04);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xe2,
					 0x00, 0x0f, 0x12, 0x21, 0x23, 0x36,
					 0x37, 0x64, 0x5a, 0x75, 0x8a, 0x74,
					 0x86, 0x5a, 0x58, 0x29, 0x2e, 0x25,
					 0x1b, 0x04);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x80);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xca,
					 0x80, 0x79, 0x82, 0x8b, 0x94, 0x9d,
					 0xa6, 0xaf, 0xb8, 0xc0, 0xc9, 0xd2,
					 0xdb, 0xe4, 0xed, 0xf6, 0x9f, 0xff,
					 0x9f, 0xff, 0x70, 0xff, 0x05, 0x03,
					 0x05, 0x03, 0x05, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc6, 0x10);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc7,
					 0xd0, 0xba, 0xab, 0xcd, 0xb9, 0xdc,
					 0xba, 0xbb, 0xbc, 0x88, 0x88, 0x67,
					 0x45, 0x44, 0x44, 0x44, 0x33, 0x33);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc6, 0x11);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc7,
					 0xc0, 0xba, 0xab, 0xcb, 0xb9, 0xcc,
					 0xa9, 0xac, 0xcb, 0x88, 0x88, 0x78,
					 0x45, 0x44, 0x44, 0x44, 0x44, 0x44);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc6, 0x12);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc7,
					 0xc0, 0xc9, 0x9a, 0xcb, 0x99, 0xcc,
					 0xaa, 0xba, 0xba, 0x88, 0x88, 0x78,
					 0x56, 0x55, 0x55, 0x44, 0x44, 0x44);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc6, 0x13);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc7,
					 0xc0, 0xb8, 0xaa, 0xca, 0x99, 0xcb,
					 0x9a, 0xaa, 0xba, 0x88, 0x88, 0x78,
					 0x56, 0x55, 0x55, 0x55, 0x55, 0x45);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc6, 0x14);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc7,
					 0xb0, 0xa9, 0x9a, 0xbb, 0x99, 0xba,
					 0x9b, 0xa9, 0xaa, 0x88, 0x88, 0x88,
					 0x67, 0x56, 0x55, 0x55, 0x55, 0x55);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc6, 0x15);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc7,
					 0xb0, 0xa8, 0x9a, 0xc9, 0xa8, 0xba,
					 0x99, 0xb9, 0x9a, 0x88, 0x88, 0x88,
					 0x67, 0x66, 0x66, 0x56, 0x55, 0x55);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc6, 0x16);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc7,
					 0xb0, 0xa8, 0x99, 0xb9, 0x8a, 0xaa,
					 0xa9, 0xa8, 0xb9, 0x88, 0x88, 0x88,
					 0x67, 0x66, 0x66, 0x66, 0x66, 0x55);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc6, 0x17);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc7,
					 0xa0, 0xa8, 0x99, 0xb9, 0x98, 0xb9,
					 0x99, 0x99, 0xa9, 0x88, 0x88, 0x88,
					 0x78, 0x66, 0x66, 0x66, 0x66, 0x66);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc6, 0x18);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc7,
					 0xa0, 0xa8, 0x99, 0xb8, 0x88, 0xa9,
					 0x9a, 0x89, 0x9a, 0x88, 0x88, 0x88,
					 0x78, 0x77, 0x67, 0x66, 0x66, 0x66);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc6, 0x19);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc7,
					 0xa0, 0x98, 0x99, 0xa8, 0x89, 0xa8,
					 0x9a, 0x98, 0x99, 0x88, 0x88, 0x88,
					 0x78, 0x77, 0x77, 0x77, 0x66, 0x66);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc6, 0x1a);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc7,
					 0xa0, 0x9a, 0x99, 0x99, 0x88, 0xa9,
					 0x98, 0x88, 0x99, 0x88, 0x88, 0x88,
					 0x78, 0x88, 0x77, 0x77, 0x77, 0x77);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc6, 0x1b);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc7,
					 0xa0, 0x9a, 0x99, 0x99, 0x88, 0xa8,
					 0x98, 0x88, 0x99, 0x88, 0x88, 0x88,
					 0x88, 0x78, 0x77, 0x77, 0x77, 0x77);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc6, 0x1c);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc7,
					 0xa0, 0xaa, 0x99, 0x98, 0x88, 0x98,
					 0x98, 0x88, 0x89, 0x88, 0x88, 0x88,
					 0x88, 0x88, 0x88, 0x77, 0x77, 0x77);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc6, 0x1d);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc7,
					 0xa0, 0xaa, 0x99, 0x88, 0x89, 0x98,
					 0x88, 0x88, 0x89, 0x88, 0x88, 0x88,
					 0x88, 0x88, 0x77, 0x77, 0x77, 0x77);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc6, 0x1e);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc7,
					 0xa0, 0xaa, 0x89, 0x88, 0x89, 0x88,
					 0x88, 0x88, 0x88, 0x88, 0x88, 0x88,
					 0x88, 0x88, 0x88, 0x88, 0x77, 0x77);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc6, 0x1f);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc7,
					 0xa0, 0xaa, 0x89, 0x88, 0x88, 0x88,
					 0x88, 0x88, 0x88, 0x88, 0x88, 0x88,
					 0x88, 0x88, 0x88, 0x88, 0x77, 0x77);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc6, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x80);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xcb,
					 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					 0x00, 0x00, 0x00, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x90);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xcb,
					 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					 0x00, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xa0);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xcb,
					 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					 0x00, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xb0);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xcb,
					 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					 0x00, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xc0);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xcb,
					 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
					 0x05, 0x05, 0x05, 0x00, 0x00, 0x00,
					 0x00, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xd0);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xcb,
					 0x00, 0x00, 0x00, 0x05, 0x05, 0x05,
					 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
					 0x05, 0x05, 0x05);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xe0);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xcb,
					 0x05, 0x00, 0x00, 0x00, 0x00, 0x00,
					 0x00, 0x00, 0x00, 0x00, 0x05, 0x05,
					 0x05, 0x05);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xf0);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xcb,
					 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
					 0xff, 0xff, 0xff, 0xff, 0xff);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x80);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xcc,
					 0x2d, 0x2d, 0x0a, 0x0c, 0x0e, 0x10,
					 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					 0x00, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x90);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xcc,
					 0x00, 0x00, 0x00, 0x2e, 0x2e, 0x02,
					 0x04, 0x2d, 0x2d, 0x09, 0x0b, 0x0d,
					 0x0f, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xa0);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xcc,
					 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					 0x00, 0x00, 0x00, 0x00, 0x2e, 0x2e,
					 0x01, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xb0);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xcc,
					 0x2d, 0x2e, 0x0f, 0x0d, 0x0b, 0x09,
					 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					 0x00, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xc0);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xcc,
					 0x00, 0x00, 0x00, 0x2e, 0x2d, 0x03,
					 0x01, 0x2d, 0x2e, 0x10, 0x0e, 0x0c,
					 0x0a, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xd0);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xcc,
					 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					 0x00, 0x00, 0x00, 0x00, 0x2e, 0x2d,
					 0x04, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x80);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xce,
					 0x8d, 0x03, 0x29, 0x8c, 0x03, 0x29,
					 0x8b, 0x03, 0x29, 0x8a, 0x03, 0x29);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x90);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xce,
					 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xa0);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xce,
					 0x38, 0x0b, 0x8b, 0x00, 0x8d, 0x29,
					 0x00, 0x38, 0x0a, 0x8b, 0x01, 0x8d,
					 0x29, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xb0);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xce,
					 0x38, 0x09, 0x8b, 0x02, 0x8d, 0x29,
					 0x00, 0x38, 0x08, 0x8b, 0x03, 0x8d,
					 0x29, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xc0);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xce,
					 0x38, 0x07, 0x8b, 0x04, 0x8d, 0x29,
					 0x00, 0x38, 0x06, 0x8b, 0x05, 0x8d,
					 0x29, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xd0);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xce,
					 0x38, 0x05, 0x8b, 0x06, 0x8d, 0x29,
					 0x00, 0x38, 0x04, 0x8b, 0x07, 0x8d,
					 0x29, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x80);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xcf,
					 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x90);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xcf,
					 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xa0);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xcf,
					 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xb0);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xcf,
					 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xc0);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xcf,
					 0x01, 0x01, 0x20, 0x20, 0x00, 0x00,
					 0x01, 0x01, 0x00, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xb5);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc5,
					 0x3c, 0x01, 0xff, 0x3c, 0x01, 0xff);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x81);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc1, 0x66);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x83);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc1, 0xb0);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_CABC_MIN_BRIGHTNESS,
				     0x0c);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x51, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x53, 0x24);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x55, 0x00);
	mipi_dsi_dcs_exit_sleep_mode_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 200);
	mipi_dsi_dcs_set_display_on_multi(&dsi_ctx);

	return dsi_ctx.accum_err;
}

static int boe_otm1284a_off(struct boe_otm1284a *ctx)
{
	struct mipi_dsi_multi_context dsi_ctx = { .dsi = ctx->dsi };

	ctx->dsi->mode_flags &= ~MIPI_DSI_MODE_LPM;

	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x28, 0x00);
	mipi_dsi_msleep(&dsi_ctx, 50);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x10, 0x00);
	mipi_dsi_msleep(&dsi_ctx, 120);

	return dsi_ctx.accum_err;
}

static int boe_otm1284a_prepare(struct drm_panel *panel)
{
	struct boe_otm1284a *ctx = to_boe_otm1284a(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(boe_otm1284a_supplies), ctx->supplies);
	if (ret < 0) {
		dev_err(dev, "Failed to enable regulators: %d\n", ret);
		return ret;
	}

	boe_otm1284a_reset(ctx);

	ret = boe_otm1284a_on(ctx);
	if (ret < 0) {
		dev_err(dev, "Failed to initialize panel: %d\n", ret);
		gpiod_set_value_cansleep(ctx->reset_gpio, 1);
		regulator_bulk_disable(ARRAY_SIZE(boe_otm1284a_supplies), ctx->supplies);
		return ret;
	}

	return 0;
}

static int boe_otm1284a_unprepare(struct drm_panel *panel)
{
	struct boe_otm1284a *ctx = to_boe_otm1284a(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	ret = boe_otm1284a_off(ctx);
	if (ret < 0)
		dev_err(dev, "Failed to un-initialize panel: %d\n", ret);

	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	regulator_bulk_disable(ARRAY_SIZE(boe_otm1284a_supplies), ctx->supplies);

	return 0;
}

static const struct drm_display_mode boe_otm1284a_mode = {
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

static int boe_otm1284a_get_modes(struct drm_panel *panel,
				  struct drm_connector *connector)
{
	return drm_connector_helper_get_modes_fixed(connector, &boe_otm1284a_mode);
}

static const struct drm_panel_funcs boe_otm1284a_panel_funcs = {
	.prepare = boe_otm1284a_prepare,
	.unprepare = boe_otm1284a_unprepare,
	.get_modes = boe_otm1284a_get_modes,
};

static int boe_otm1284a_bl_update_status(struct backlight_device *bl)
{
	struct mipi_dsi_device *dsi = bl_get_data(bl);
	u16 brightness = backlight_get_brightness(bl);
	int ret;

	dsi->mode_flags &= ~MIPI_DSI_MODE_LPM;

	ret = mipi_dsi_dcs_set_display_brightness(dsi, brightness);
	if (ret < 0)
		return ret;

	dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	return 0;
}

// TODO: Check if /sys/class/backlight/.../actual_brightness actually returns
// correct values. If not, remove this function.
static int boe_otm1284a_bl_get_brightness(struct backlight_device *bl)
{
	struct mipi_dsi_device *dsi = bl_get_data(bl);
	u16 brightness;
	int ret;

	dsi->mode_flags &= ~MIPI_DSI_MODE_LPM;

	ret = mipi_dsi_dcs_get_display_brightness(dsi, &brightness);
	if (ret < 0)
		return ret;

	dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	return brightness & 0xff;
}

static const struct backlight_ops boe_otm1284a_bl_ops = {
	.update_status = boe_otm1284a_bl_update_status,
	.get_brightness = boe_otm1284a_bl_get_brightness,
};

static struct backlight_device *
boe_otm1284a_create_backlight(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	const struct backlight_properties props = {
		.type = BACKLIGHT_RAW,
		.brightness = 255,
		.max_brightness = 255,
	};

	return devm_backlight_device_register(dev, dev_name(dev), dev, dsi,
					      &boe_otm1284a_bl_ops, &props);
}

static int boe_otm1284a_probe(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	struct boe_otm1284a *ctx;
	int ret;

	ctx = devm_drm_panel_alloc(dev, struct boe_otm1284a, panel,
				   &boe_otm1284a_panel_funcs,
				   DRM_MODE_CONNECTOR_DSI);
	if (IS_ERR(ctx))
		return PTR_ERR(ctx);

	ret = devm_regulator_bulk_get_const(dev,
					    ARRAY_SIZE(boe_otm1284a_supplies),
					    boe_otm1284a_supplies,
					    &ctx->supplies);
	if (ret < 0)
		return ret;

	ctx->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	if (IS_ERR(ctx->reset_gpio))
		return dev_err_probe(dev, PTR_ERR(ctx->reset_gpio),
				     "Failed to get reset-gpios\n");

	ctx->dsi = dsi;
	mipi_dsi_set_drvdata(dsi, ctx);

	dsi->lanes = 4;
	dsi->format = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BURST |
			  MIPI_DSI_MODE_VIDEO_HSE | MIPI_DSI_MODE_NO_EOT_PACKET |
			  MIPI_DSI_CLOCK_NON_CONTINUOUS;

	ctx->panel.prepare_prev_first = true;

	ctx->panel.backlight = boe_otm1284a_create_backlight(dsi);
	if (IS_ERR(ctx->panel.backlight))
		return dev_err_probe(dev, PTR_ERR(ctx->panel.backlight),
				     "Failed to create backlight\n");

	ret = devm_drm_panel_add(dev, &ctx->panel);
	if (ret)
		return ret;

	return devm_mipi_dsi_attach(dev, dsi);
}

static const struct of_device_id boe_otm1284a_of_match[] = {
	{ .compatible = "boe,otm1284a" }, // FIXME
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, boe_otm1284a_of_match);

static struct mipi_dsi_driver boe_otm1284a_driver = {
	.probe = boe_otm1284a_probe,
	.driver = {
		.name = "panel-boe-otm1284a",
		.of_match_table = boe_otm1284a_of_match,
	},
};
module_mipi_dsi_driver(boe_otm1284a_driver);

MODULE_AUTHOR("linux-mdss-dsi-panel-driver-generator <fix@me>"); // FIXME
MODULE_DESCRIPTION("DRM driver for boe 720p video mode dsi panel");
MODULE_LICENSE("GPL");
