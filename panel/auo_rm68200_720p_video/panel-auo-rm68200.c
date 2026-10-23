// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2026 FIXME
// Generated with linux-mdss-dsi-panel-driver-generator from vendor device tree:
//   Copyright (c) 2013, The Linux Foundation. All rights reserved. (FIXME)

#include <linux/array_size.h>
#include <linux/backlight.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/gpio/consumer.h>
#include <linux/mod_devicetable.h>
#include <linux/module.h>
#include <linux/regulator/consumer.h>

#include <video/mipi_display.h>

#include <drm/drm_mipi_dsi.h>
#include <drm/drm_modes.h>
#include <drm/drm_panel.h>
#include <drm/drm_probe_helper.h>

struct auo_rm68200 {
	struct drm_panel panel;
	struct mipi_dsi_device *dsi;
	struct regulator_bulk_data *supplies;
	struct gpio_desc *reset_gpio;
	struct gpio_desc *backlight_gpio;
};

static const struct regulator_bulk_data auo_rm68200_supplies[] = {
	{ .supply = "vdd" },
	{ .supply = "vddio" },
};

static inline struct auo_rm68200 *to_auo_rm68200(struct drm_panel *panel)
{
	return container_of(panel, struct auo_rm68200, panel);
}

static void auo_rm68200_reset(struct auo_rm68200 *ctx)
{
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	usleep_range(10000, 11000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	usleep_range(10000, 11000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	usleep_range(10000, 11000);
}

static int auo_rm68200_on(struct auo_rm68200 *ctx)
{
	struct mipi_dsi_multi_context dsi_ctx = { .dsi = ctx->dsi };

	ctx->dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xfe, 0x04);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5f, 0x0a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x60, 0x09);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x61, 0x11);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x62, 0x18);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x63, 0x09);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x64, 0x03);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x65, 0x0f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x66, 0x10);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x67, 0x0d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x68, 0x15);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x69, 0x0b);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6a, 0x0d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6b, 0x07);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6c, 0x0f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6d, 0x11);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6e, 0x0e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x09);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x70, 0x09);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x71, 0x11);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x72, 0x18);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x73, 0x09);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x74, 0x03);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x75, 0x0f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x76, 0x10);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x77, 0x0d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x78, 0x15);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x79, 0x0b);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7a, 0x0d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7b, 0x07);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7c, 0x0f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7d, 0x11);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7e, 0x0e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7f, 0x09);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1c, 0x33);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1d, 0x44);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1e, 0x55);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1f, 0x67);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x20, 0x89);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x21, 0xab);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0a, 0x62);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x15, 0xfe);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x27, 0x5b);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xfe, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_CABC_MIN_BRIGHTNESS,
				     0x0c);
	mipi_dsi_dcs_set_display_brightness_multi(&dsi_ctx, 0x0000);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_CONTROL_DISPLAY,
				     0x24);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_POWER_SAVE, 0x00);
	mipi_dsi_dcs_exit_sleep_mode_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 150);
	mipi_dsi_dcs_set_display_on_multi(&dsi_ctx);

	return dsi_ctx.accum_err;
}

static int auo_rm68200_off(struct auo_rm68200 *ctx)
{
	struct mipi_dsi_multi_context dsi_ctx = { .dsi = ctx->dsi };

	ctx->dsi->mode_flags &= ~MIPI_DSI_MODE_LPM;

	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x28, 0x00);
	mipi_dsi_msleep(&dsi_ctx, 50);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x10, 0x00);
	mipi_dsi_msleep(&dsi_ctx, 120);

	return dsi_ctx.accum_err;
}

static int auo_rm68200_prepare(struct drm_panel *panel)
{
	struct auo_rm68200 *ctx = to_auo_rm68200(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(auo_rm68200_supplies), ctx->supplies);
	if (ret < 0) {
		dev_err(dev, "Failed to enable regulators: %d\n", ret);
		return ret;
	}

	auo_rm68200_reset(ctx);
	gpiod_set_value_cansleep(ctx->backlight_gpio, 1);

	ret = auo_rm68200_on(ctx);
	if (ret < 0) {
		dev_err(dev, "Failed to initialize panel: %d\n", ret);
		gpiod_set_value_cansleep(ctx->backlight_gpio, 0);
		gpiod_set_value_cansleep(ctx->reset_gpio, 1);
		regulator_bulk_disable(ARRAY_SIZE(auo_rm68200_supplies), ctx->supplies);
		return ret;
	}

	return 0;
}

static int auo_rm68200_unprepare(struct drm_panel *panel)
{
	struct auo_rm68200 *ctx = to_auo_rm68200(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	ret = auo_rm68200_off(ctx);
	if (ret < 0)
		dev_err(dev, "Failed to un-initialize panel: %d\n", ret);

	gpiod_set_value_cansleep(ctx->backlight_gpio, 0);
	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	regulator_bulk_disable(ARRAY_SIZE(auo_rm68200_supplies), ctx->supplies);

	return 0;
}

static const struct drm_display_mode auo_rm68200_mode = {
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

static int auo_rm68200_get_modes(struct drm_panel *panel,
				 struct drm_connector *connector)
{
	return drm_connector_helper_get_modes_fixed(connector, &auo_rm68200_mode);
}

static const struct drm_panel_funcs auo_rm68200_panel_funcs = {
	.prepare = auo_rm68200_prepare,
	.unprepare = auo_rm68200_unprepare,
	.get_modes = auo_rm68200_get_modes,
};

static int auo_rm68200_bl_update_status(struct backlight_device *bl)
{
	struct mipi_dsi_device *dsi = bl_get_data(bl);
	struct auo_rm68200 *ctx = mipi_dsi_get_drvdata(dsi);
	u16 brightness = backlight_get_brightness(bl);
	int ret;

	gpiod_set_value_cansleep(ctx->backlight_gpio, !!brightness);

	dsi->mode_flags &= ~MIPI_DSI_MODE_LPM;

	ret = mipi_dsi_dcs_set_display_brightness(dsi, brightness);
	if (ret < 0)
		return ret;

	dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	return 0;
}

static const struct backlight_ops auo_rm68200_bl_ops = {
	.update_status = auo_rm68200_bl_update_status,
};

static struct backlight_device *
auo_rm68200_create_backlight(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	const struct backlight_properties props = {
		.type = BACKLIGHT_RAW,
		.brightness = 255,
		.max_brightness = 255,
	};

	return devm_backlight_device_register(dev, dev_name(dev), dev, dsi,
					      &auo_rm68200_bl_ops, &props);
}

static int auo_rm68200_probe(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	struct auo_rm68200 *ctx;
	int ret;

	ctx = devm_kzalloc(dev, sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	ret = devm_regulator_bulk_get_const(dev,
					    ARRAY_SIZE(auo_rm68200_supplies),
					    auo_rm68200_supplies,
					    &ctx->supplies);
	if (ret < 0)
		return ret;

	ctx->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	if (IS_ERR(ctx->reset_gpio))
		return dev_err_probe(dev, PTR_ERR(ctx->reset_gpio),
				     "Failed to get reset-gpios\n");

	ctx->backlight_gpio = devm_gpiod_get(dev, "backlight", GPIOD_OUT_LOW);
	if (IS_ERR(ctx->backlight_gpio))
		return dev_err_probe(dev, PTR_ERR(ctx->backlight_gpio),
				     "Failed to get backlight-gpios\n");

	ctx->dsi = dsi;
	mipi_dsi_set_drvdata(dsi, ctx);

	dsi->lanes = 4;
	dsi->format = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BURST |
			  MIPI_DSI_MODE_VIDEO_HSE | MIPI_DSI_MODE_NO_EOT_PACKET |
			  MIPI_DSI_CLOCK_NON_CONTINUOUS;

	drm_panel_init(&ctx->panel, dev, &auo_rm68200_panel_funcs,
		       DRM_MODE_CONNECTOR_DSI);
	ctx->panel.prepare_prev_first = true;

	ctx->panel.backlight = auo_rm68200_create_backlight(dsi);
	if (IS_ERR(ctx->panel.backlight))
		return dev_err_probe(dev, PTR_ERR(ctx->panel.backlight),
				     "Failed to create backlight\n");

	drm_panel_add(&ctx->panel);

	ret = mipi_dsi_attach(dsi);
	if (ret < 0) {
		drm_panel_remove(&ctx->panel);
		return dev_err_probe(dev, ret, "Failed to attach to DSI host\n");
	}

	return 0;
}

static void auo_rm68200_remove(struct mipi_dsi_device *dsi)
{
	struct auo_rm68200 *ctx = mipi_dsi_get_drvdata(dsi);

	mipi_dsi_detach(dsi);
	drm_panel_remove(&ctx->panel);
}

static const struct of_device_id auo_rm68200_of_match[] = {
	{ .compatible = "asus,z00e-auo-rm68200" },
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, auo_rm68200_of_match);

static struct mipi_dsi_driver auo_rm68200_driver = {
	.probe = auo_rm68200_probe,
	.remove = auo_rm68200_remove,
	.driver = {
		.name = "panel-asus-z00e-auo-rm68200",
		.of_match_table = auo_rm68200_of_match,
	},
};
module_mipi_dsi_driver(auo_rm68200_driver);

MODULE_AUTHOR("linux-mdss-dsi-panel-driver-generator");
MODULE_DESCRIPTION("DRM driver for auo 720p video mode dsi panel");
MODULE_LICENSE("GPL");
