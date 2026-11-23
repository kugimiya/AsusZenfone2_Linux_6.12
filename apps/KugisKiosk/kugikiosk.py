#!/usr/bin/env python3
"""KugisKiosk — fullscreen Cage UI driven by ~/.kugikiosk.yaml + ~/.kugikiosk.sh."""

from __future__ import annotations

import math
import os
import subprocess
import sys
from pathlib import Path

import gi
import yaml

gi.require_version("Gtk", "4.0")
gi.require_version("Gdk", "4.0")
from gi.repository import Gdk, GLib, Gtk  # noqa: E402

HOME = Path.home()
CONFIG_PATH = HOME / ".kugikiosk.yaml"
SCRIPT_PATH = HOME / ".kugikiosk.sh"

DEFAULT_CONFIG = {
    "orientation": "portrait",  # portrait | portrait-flipped | landscape | landscape-flipped
    "anchor": "center",  # center | top-left | top-right | bottom-left | bottom-right
    "font_size": 28,
    "background": "#0f172a",
    "foreground": "#f8fafc",
    "border_color": "#38bdf8",
    "border_radius": 12,
    "padding": 16,  # inside bordered [...] boxes
    "edge_padding": 16,  # inset from screen edges
    "gap": 12,
    # How often to re-run ~/.kugikiosk.sh
    "script_interval_seconds": 10,
}

DEFAULT_SCRIPT = """\
#!/bin/sh
echo "[internal]"
echo "$(hostname)"
date "+%H:%M:%S  %Y-%m-%d"
uptime
"""


DEFAULT_CONFIG_TEXT = "\n".join(
    [
        "#Параметр\tТип\tДефолт\tЧто делает",
        "#orientation\tstring\tportrait\tportrait / portrait-flipped / landscape / landscape-flipped",
        "#anchor\tstring\tcenter\tcenter / top-left / top-right / bottom-left / bottom-right",
        "#font_size\tint\t28\tразмер шрифта",
        "#background\thex\t#0f172a\tфон",
        "#foreground\thex\t#f8fafc\tцвет текста",
        "#border_color\thex\t#38bdf8\tцвет рамки у строк в [...]",
        "#border_radius\tint\t12\tскругление рамки",
        "#padding\tint\t16\tотступ внутри рамки [...]",
        "#edge_padding\tint\t16\tотступ блока текста от краёв экрана",
        "#gap\tint\t12\tрасстояние между строками",
        "#script_interval_seconds\tfloat\t10\tпериод перезапуска ~/.kugikiosk.sh (минимум 0.5)",
        "",
        "orientation: portrait",
        "anchor: center",
        "font_size: 28",
        "background: \"#0f172a\"",
        "foreground: \"#f8fafc\"",
        "border_color: \"#38bdf8\"",
        "border_radius: 12",
        "padding: 16",
        "edge_padding: 16",
        "gap: 12",
        "script_interval_seconds: 10",
        "",
    ]
)

ORIENT = {
    "portrait": 0,
    "portrait-flipped": 180,
    "landscape": 90,
    "landscape-flipped": 270,
}

ANCHORS = {
    "center",
    "top-left",
    "top-right",
    "bottom-left",
    "bottom-right",
}


def parse_color(value: str) -> tuple[float, float, float, float]:
    s = (value or "#000000").strip().lstrip("#")
    if len(s) == 3:
        s = "".join(ch * 2 for ch in s)
    if len(s) != 6:
        return 0.0, 0.0, 0.0, 1.0
    r = int(s[0:2], 16) / 255.0
    g = int(s[2:4], 16) / 255.0
    b = int(s[4:6], 16) / 255.0
    return r, g, b, 1.0


def file_mtime(path: Path) -> float:
    try:
        return path.stat().st_mtime
    except OSError:
        return -1.0


def ensure_files() -> None:
    """Create ~/.kugikiosk.yaml and ~/.kugikiosk.sh with defaults if missing."""
    if not CONFIG_PATH.exists():
        CONFIG_PATH.write_text(DEFAULT_CONFIG_TEXT, encoding="utf-8")
        print(f"KugisKiosk: created default config {CONFIG_PATH}", file=sys.stderr)
    if not SCRIPT_PATH.exists():
        SCRIPT_PATH.write_text(DEFAULT_SCRIPT, encoding="utf-8")
        SCRIPT_PATH.chmod(0o755)
        print(f"KugisKiosk: created default script {SCRIPT_PATH}", file=sys.stderr)


def load_config() -> dict:
    ensure_files()
    cfg = dict(DEFAULT_CONFIG)
    data: dict = {}
    try:
        loaded = yaml.safe_load(CONFIG_PATH.read_text(encoding="utf-8")) or {}
        if isinstance(loaded, dict):
            data = loaded
            cfg.update({k: v for k, v in data.items() if v is not None})
    except Exception as exc:
        print(f"KugisKiosk: config error: {exc}", file=sys.stderr)

    orient = str(cfg.get("orientation", "portrait")).strip().lower().replace("_", "-")
    if orient not in ORIENT:
        orient = "portrait"
    cfg["orientation"] = orient

    anchor = str(cfg.get("anchor", "center")).strip().lower().replace("_", "-")
    if anchor not in ANCHORS:
        anchor = "center"
    cfg["anchor"] = anchor

    # Prefer script_interval_seconds; accept legacy refresh_seconds
    if "script_interval_seconds" in data:
        interval = data.get("script_interval_seconds")
    elif "refresh_seconds" in data:
        interval = data.get("refresh_seconds")
    else:
        interval = cfg.get("script_interval_seconds", 10)
    try:
        cfg["script_interval_seconds"] = float(interval)
    except Exception:
        cfg["script_interval_seconds"] = float(DEFAULT_CONFIG["script_interval_seconds"])
    cfg["script_interval_seconds"] = max(0.5, cfg["script_interval_seconds"])

    for key, cast in (
        ("font_size", int),
        ("border_radius", int),
        ("padding", int),
        ("edge_padding", int),
        ("gap", int),
    ):
        try:
            cfg[key] = cast(cfg[key])
        except Exception:
            cfg[key] = DEFAULT_CONFIG[key]
    cfg["padding"] = max(0, int(cfg["padding"]))
    cfg["edge_padding"] = max(0, int(cfg["edge_padding"]))
    return cfg


def run_script() -> list[tuple[str, bool]]:
    """Return list of (text, bordered). bordered if whole line wrapped in []."""
    ensure_files()
    try:
        proc = subprocess.run(
            ["sh", str(SCRIPT_PATH)],
            capture_output=True,
            text=True,
            timeout=30,
            check=False,
            env={**os.environ, "HOME": str(HOME)},
        )
        out = proc.stdout or ""
        if proc.returncode != 0 and proc.stderr:
            out += ("\n" if out and not out.endswith("\n") else "") + proc.stderr
    except subprocess.TimeoutExpired:
        out = "[script timeout]"
    except Exception as exc:
        out = f"[script error: {exc}]"

    lines: list[tuple[str, bool]] = []
    for raw in out.splitlines():
        s = raw.rstrip("\n")
        stripped = s.strip()
        if len(stripped) >= 2 and stripped.startswith("[") and stripped.endswith("]"):
            lines.append((stripped[1:-1], True))
        else:
            lines.append((s, False))
    if not lines:
        lines.append(("(no output)", False))
    return lines


def rounded_rect(cr, x, y, w, h, radius: float) -> None:
    r = max(0.0, min(float(radius), w / 2.0, h / 2.0))
    cr.new_sub_path()
    cr.arc(x + w - r, y + r, r, -math.pi / 2, 0)
    cr.arc(x + w - r, y + h - r, r, 0, math.pi / 2)
    cr.arc(x + r, y + h - r, r, math.pi / 2, math.pi)
    cr.arc(x + r, y + r, r, math.pi, 3 * math.pi / 2)
    cr.close_path()


class KugisKiosk(Gtk.Application):
    def __init__(self):
        super().__init__(application_id="eco.nura.KugisKiosk")
        self.cfg = load_config()
        self.lines = run_script()
        self.area = None
        self._config_mtime = file_mtime(CONFIG_PATH)
        self._script_mtime = file_mtime(SCRIPT_PATH)
        self._watch_id = 0
        self._script_id = 0

    def do_activate(self):
        win = Gtk.ApplicationWindow(application=self, title="KugisKiosk")
        win.set_decorated(False)
        win.set_default_size(720, 1280)

        area = Gtk.DrawingArea()
        area.set_draw_func(self._on_draw)
        area.set_hexpand(True)
        area.set_vexpand(True)
        self.area = area
        win.set_child(area)

        key = Gtk.EventControllerKey()

        def on_key(_c, keyval, *_a):
            if keyval in (Gdk.KEY_Escape, Gdk.KEY_q, Gdk.KEY_Q):
                self.quit()
                return True
            if keyval in (Gdk.KEY_r, Gdk.KEY_R, Gdk.KEY_F5):
                self._reload_config(force=True)
                self._rerun_script()
                return True
            return False

        key.connect("key-pressed", on_key)
        win.add_controller(key)

        win.present()
        win.fullscreen()

        # Poll files often; script runs on its own interval from config.
        self._watch_id = GLib.timeout_add(1000, self._on_watch)
        self._arm_script_timer()
        print(
            f"KugisKiosk: config={CONFIG_PATH} script={SCRIPT_PATH} "
            f"orient={self.cfg['orientation']} "
            f"script_interval={self.cfg['script_interval_seconds']}s",
            file=sys.stderr,
        )

    def _arm_script_timer(self) -> None:
        if self._script_id:
            GLib.source_remove(self._script_id)
            self._script_id = 0
        ms = int(float(self.cfg["script_interval_seconds"]) * 1000)
        self._script_id = GLib.timeout_add(ms, self._on_script_timer)

    def _on_script_timer(self):
        self._rerun_script()
        # Re-arm in case interval changed mid-flight; returning True keeps old period.
        # We manage period via _arm_script_timer on config reload, so True is fine
        # when interval unchanged.
        return True

    def _on_watch(self):
        ensure_files()
        cfg_m = file_mtime(CONFIG_PATH)
        script_m = file_mtime(SCRIPT_PATH)

        if cfg_m != self._config_mtime:
            self._config_mtime = cfg_m
            print("KugisKiosk: config changed — reloading", file=sys.stderr)
            self._reload_config(force=True)

        if script_m != self._script_mtime:
            self._script_mtime = script_m
            print("KugisKiosk: script changed — re-running", file=sys.stderr)
            self._rerun_script()

        return True

    def _reload_config(self, force: bool = False) -> None:
        old_interval = self.cfg.get("script_interval_seconds")
        self.cfg = load_config()
        self._config_mtime = file_mtime(CONFIG_PATH)
        if force or self.cfg.get("script_interval_seconds") != old_interval:
            self._arm_script_timer()
        if self.area:
            self.area.queue_draw()

    def _rerun_script(self) -> None:
        self.lines = run_script()
        self._script_mtime = file_mtime(SCRIPT_PATH)
        if self.area:
            self.area.queue_draw()

    def _content_size(self, alloc_w: int, alloc_h: int) -> tuple[int, int]:
        deg = ORIENT[self.cfg["orientation"]]
        if deg in (90, 270):
            return alloc_h, alloc_w
        return alloc_w, alloc_h

    def _on_draw(self, _area, cr, width: int, height: int):
        import cairo

        cfg = self.cfg
        bg = parse_color(str(cfg["background"]))
        fg = parse_color(str(cfg["foreground"]))
        bd = parse_color(str(cfg["border_color"]))
        font_size = max(8, int(cfg["font_size"]))
        pad = max(0, int(cfg["padding"]))
        edge = max(0, int(cfg["edge_padding"]))
        gap = max(0, int(cfg["gap"]))
        radius = max(0, int(cfg["border_radius"]))
        deg = ORIENT[cfg["orientation"]]
        anchor = cfg.get("anchor", "center")

        cr.set_source_rgba(*bg)
        cr.paint()

        cr.save()
        if deg == 0:
            cr.translate(0, 0)
        elif deg == 180:
            cr.translate(width, height)
            cr.rotate(math.pi)
        elif deg == 90:
            cr.translate(width, 0)
            cr.rotate(math.pi / 2)
        elif deg == 270:
            cr.translate(0, height)
            cr.rotate(-math.pi / 2)

        cw, ch = self._content_size(width, height)
        area_x = edge
        area_y = edge
        area_w = max(0, cw - 2 * edge)
        area_h = max(0, ch - 2 * edge)

        cr.select_font_face(
            "DejaVu Sans", cairo.FONT_SLANT_NORMAL, cairo.FONT_WEIGHT_NORMAL
        )
        cr.set_font_size(font_size)

        metrics = []
        total_h = 0
        for text, bordered in self.lines:
            xb, yb, tw, th, _dx, _dy = cr.text_extents(text if text else " ")
            box_w = tw + (2 * pad if bordered else 0)
            box_h = th + (2 * pad if bordered else 0)
            metrics.append((text, bordered, xb, yb, tw, th, box_w, box_h))
            total_h += box_h
        if self.lines:
            total_h += gap * (len(self.lines) - 1)

        if anchor.startswith("top"):
            y = area_y
        elif anchor.startswith("bottom"):
            y = area_y + max(0, area_h - total_h)
        else:
            y = area_y + max(0, (area_h - total_h) / 2)

        for text, bordered, xb, yb, tw, th, box_w, box_h in metrics:
            if anchor.endswith("left"):
                x = area_x
            elif anchor.endswith("right"):
                x = area_x + max(0, area_w - box_w)
            else:
                x = area_x + max(0, (area_w - box_w) / 2)
            if bordered:
                rounded_rect(cr, x, y, box_w, box_h, radius)
                cr.set_source_rgba(*bd)
                cr.set_line_width(max(2.0, font_size / 14.0))
                cr.stroke()
                tx = x + pad - xb
                ty = y + pad - yb
            else:
                tx = x - xb
                ty = y - yb
            cr.set_source_rgba(*fg)
            cr.move_to(tx, ty)
            cr.show_text(text)
            y += box_h + gap

        cr.restore()


def main(argv):
    os.environ.setdefault("GDK_BACKEND", "wayland")
    os.environ.setdefault("GSK_RENDERER", "gl")
    ensure_files()
    app = KugisKiosk()
    return app.run(argv)


if __name__ == "__main__":
    sys.exit(main(sys.argv) or 0)
