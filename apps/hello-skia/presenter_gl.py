#!/usr/bin/env python3
"""Fullscreen Hello World on Adreno 306 via GTK4 GLArea (OpenGL ES).

Skia-canvas GPU needs Vulkan; this SoC has none. Freedreno GLES works, so the
kiosk scene is drawn on the GPU. Optional stdin: lines "t=<float>" update time.
"""

from __future__ import annotations

import ctypes
import math
import os
import sys

import gi

gi.require_version("Gtk", "4.0")
gi.require_version("Gdk", "4.0")
from gi.repository import Gdk, GLib, Gtk  # noqa: E402

VERT = b"""#version 100
attribute vec2 a_pos;
varying vec2 v_uv;
void main() {
  v_uv = a_pos * 0.5 + 0.5;
  gl_Position = vec4(a_pos, 0.0, 1.0);
}
"""

FRAG = b"""#version 100
precision mediump float;
varying vec2 v_uv;
uniform float u_t;
uniform vec2 u_res;

void main() {
  vec2 p = v_uv;
  vec3 top = vec3(0.059, 0.090, 0.165);
  vec3 bot = vec3(0.118, 0.161, 0.231);
  vec3 col = mix(top, bot, p.y);

  vec2 orb = vec2(0.5 + 0.055 * cos(u_t), 0.38 + 0.019 * sin(u_t * 1.3));
  // account for aspect so the orb stays round
  vec2 d = (p - orb) * vec2(u_res.x / u_res.y, 1.0);
  float r = length(d);
  float glow = exp(-r * r * 18.0);
  col += vec3(0.22, 0.74, 0.97) * glow * 0.55;

  // soft title bar band (text is overlaid via Cairo texture in a second pass)
  gl_FragColor = vec4(col, 1.0);
}
"""

TEXT_VERT = b"""#version 100
attribute vec2 a_pos;
attribute vec2 a_uv;
varying vec2 v_uv;
void main() {
  v_uv = a_uv;
  gl_Position = vec4(a_pos, 0.0, 1.0);
}
"""

TEXT_FRAG = b"""#version 100
precision mediump float;
varying vec2 v_uv;
uniform sampler2D u_tex;
void main() {
  vec4 c = texture2D(u_tex, v_uv);
  if (c.a < 0.01) discard;
  gl_FragColor = c;
}
"""


class GlHello(Gtk.Application):
    def __init__(self):
        super().__init__(application_id="eco.nura.HelloSkia")
        self.t = 0.0
        self._gl = None
        self._prog = 0
        self._text_prog = 0
        self._vbo = 0
        self._text_vbo = 0
        self._text_tex = 0
        self._text_size = (1, 1)
        self._tick = None

    def do_activate(self):
        win = Gtk.ApplicationWindow(application=self, title="Hello Skia GL")
        win.set_decorated(False)
        win.set_default_size(720, 1280)

        area = Gtk.GLArea()
        try:
            area.set_allowed_apis(Gdk.GLAPI.GLES)
        except Exception:
            pass
        try:
            area.set_required_version(2, 0)
            area.set_use_es(True)
        except Exception:
            pass
        area.set_has_depth_buffer(False)
        area.set_auto_render(True)
        area.connect("realize", self._on_realize)
        area.connect("render", self._on_render)
        area.connect("resize", self._on_resize)
        self.area = area
        win.set_child(area)

        click = Gtk.GestureClick()
        # In kiosk mode, ignore tap-to-quit unless HELLO_SKIA_TAP_QUIT=1
        if os.environ.get("HELLO_SKIA_TAP_QUIT", "") == "1":
            click.connect("pressed", lambda *a: self.quit())
            win.add_controller(click)

        key = Gtk.EventControllerKey()

        def on_key(_c, keyval, *_a):
            if keyval in (Gdk.KEY_Escape, Gdk.KEY_q, Gdk.KEY_Q):
                self.quit()
                return True
            return False

        key.connect("key-pressed", on_key)
        win.add_controller(key)

        win.present()
        win.fullscreen()

        GLib.io_add_watch(
            sys.stdin.buffer,
            GLib.IO_IN | GLib.IO_HUP | GLib.IO_ERR,
            self._on_stdin,
        )
        # ~30 FPS is enough for this demo and keeps the A53 cool.
        self._tick = GLib.timeout_add(33, self._on_tick)

    def _on_tick(self):
        self.t += 0.025
        if self.area.get_realized():
            self.area.queue_render()
        return True

    def _on_stdin(self, _source, condition):
        if condition & (GLib.IO_HUP | GLib.IO_ERR):
            return False
        line = sys.stdin.buffer.readline()
        if not line:
            return False
        try:
            text = line.decode().strip()
            if text.startswith("t="):
                self.t = float(text[2:])
        except Exception:
            pass
        return True

    def _on_resize(self, _area, width, height):
        self._width = max(width, 1)
        self._height = max(height, 1)

    def _on_realize(self, area):
        area.make_current()
        if area.get_error():
            print("GL realize error:", area.get_error(), file=sys.stderr)
            return
        from OpenGL import GL

        self._gl = GL
        self._prog = self._compile(GL, VERT, FRAG)
        self._text_prog = self._compile(GL, TEXT_VERT, TEXT_FRAG)
        self._vbo = GL.glGenBuffers(1)
        verts = (ctypes.c_float * 12)(-1, -1, 1, -1, -1, 1, 1, -1, 1, 1, -1, 1)
        GL.glBindBuffer(GL.GL_ARRAY_BUFFER, self._vbo)
        GL.glBufferData(GL.GL_ARRAY_BUFFER, ctypes.sizeof(verts), verts, GL.GL_STATIC_DRAW)

        self._text_vbo = GL.glGenBuffers(1)
        self._upload_text_atlas(GL)
        print("hello-skia: GLES presenter ready", file=sys.stderr)

    def _compile(self, GL, vert_src, frag_src):
        def sh(ftype, src):
            s = GL.glCreateShader(ftype)
            text = src.decode() if isinstance(src, (bytes, bytearray)) else src
            GL.glShaderSource(s, text)
            GL.glCompileShader(s)
            ok = GL.glGetShaderiv(s, GL.GL_COMPILE_STATUS)
            if not ok:
                raise RuntimeError(str(GL.glGetShaderInfoLog(s)))
            return s

        prog = GL.glCreateProgram()
        vs = sh(GL.GL_VERTEX_SHADER, vert_src)
        fs = sh(GL.GL_FRAGMENT_SHADER, frag_src)
        GL.glAttachShader(prog, vs)
        GL.glAttachShader(prog, fs)
        GL.glLinkProgram(prog)
        if not GL.glGetProgramiv(prog, GL.GL_LINK_STATUS):
            raise RuntimeError(GL.glGetProgramInfoLog(prog))
        GL.glDeleteShader(vs)
        GL.glDeleteShader(fs)
        return prog

    def _upload_text_atlas(self, GL):
        import cairo

        # Compact atlas (not full screen) — avoids a multi-second CPU swizzle.
        tw, th = 720, 420
        surface = cairo.ImageSurface(cairo.FORMAT_ARGB32, tw, th)
        cr = cairo.Context(surface)
        cr.set_operator(cairo.OPERATOR_CLEAR)
        cr.paint()
        cr.set_operator(cairo.OPERATOR_OVER)

        def draw_centered(y, size, rgba, label, bold=False):
            cr.select_font_face(
                "DejaVu Sans",
                cairo.FONT_SLANT_NORMAL,
                cairo.FONT_WEIGHT_BOLD if bold else cairo.FONT_WEIGHT_NORMAL,
            )
            cr.set_font_size(size)
            xb, _yb, w, _h, _dx, _dy = cr.text_extents(label)
            cr.set_source_rgba(*rgba)
            cr.move_to((tw - w) / 2 - xb, y)
            cr.show_text(label)

        draw_centered(90, 64, (0.973, 0.980, 0.988, 1), "Hello, World!", True)
        draw_centered(160, 28, (0.580, 0.639, 0.722, 1), "GLES on Zenfone 2 Laser")
        draw_centered(205, 22, (0.392, 0.455, 0.545, 1), "Cage · Wayland · Adreno 306")
        draw_centered(360, 24, (0.220, 0.741, 0.973, 1), "kiosk mode")
        surface.flush()

        # Prefer EXT_texture_format_BGRA8888 to skip CPU swizzle.
        buf = bytes(surface.get_data())
        ext = GL.glGetString(GL.GL_EXTENSIONS) or b""
        if isinstance(ext, bytes):
            ext_s = ext.decode()
        else:
            ext_s = str(ext)
        use_bgra = "GL_EXT_texture_format_BGRA8888" in ext_s

        self._text_tex = GL.glGenTextures(1)
        GL.glBindTexture(GL.GL_TEXTURE_2D, self._text_tex)
        GL.glTexParameteri(GL.GL_TEXTURE_2D, GL.GL_TEXTURE_MIN_FILTER, GL.GL_LINEAR)
        GL.glTexParameteri(GL.GL_TEXTURE_2D, GL.GL_TEXTURE_MAG_FILTER, GL.GL_LINEAR)
        GL.glTexParameteri(GL.GL_TEXTURE_2D, GL.GL_TEXTURE_WRAP_S, GL.GL_CLAMP_TO_EDGE)
        GL.glTexParameteri(GL.GL_TEXTURE_2D, GL.GL_TEXTURE_WRAP_T, GL.GL_CLAMP_TO_EDGE)
        GL.glPixelStorei(GL.GL_UNPACK_ALIGNMENT, 4)
        if use_bgra:
            fmt = GL.GL_BGRA_EXT if hasattr(GL, "GL_BGRA_EXT") else 0x80E1
            GL.glTexImage2D(
                GL.GL_TEXTURE_2D, 0, fmt, tw, th, 0, fmt, GL.GL_UNSIGNED_BYTE, buf
            )
        else:
            # Fallback: one-shot swizzle via array module (faster than pure Python loop)
            import array

            a = array.array("B", buf)
            for i in range(0, len(a), 4):
                a[i], a[i + 2] = a[i + 2], a[i]
            GL.glTexImage2D(
                GL.GL_TEXTURE_2D,
                0,
                GL.GL_RGBA,
                tw,
                th,
                0,
                GL.GL_RGBA,
                GL.GL_UNSIGNED_BYTE,
                a.tobytes(),
            )
        self._text_size = (tw, th)
        print("hello-skia: text atlas", tw, "x", th, "bgra" if use_bgra else "rgba", file=sys.stderr)

        # Place atlas in the middle band of the screen (NDC).
        # Phone is portrait: y up in NDC.
        y0, y1 = -0.15, 0.55
        tv = (ctypes.c_float * 24)(
            -1, y0, 0, 1,
            1, y0, 1, 1,
            -1, y1, 0, 0,
            1, y0, 1, 1,
            1, y1, 1, 0,
            -1, y1, 0, 0,
        )
        GL.glBindBuffer(GL.GL_ARRAY_BUFFER, self._text_vbo)
        GL.glBufferData(GL.GL_ARRAY_BUFFER, ctypes.sizeof(tv), tv, GL.GL_STATIC_DRAW)

    def _on_render(self, area, _ctx):
        GL = self._gl
        if GL is None:
            return True
        area.make_current()
        w = area.get_allocated_width()
        h = area.get_allocated_height()
        GL.glViewport(0, 0, max(w, 1), max(h, 1))
        GL.glClearColor(0.06, 0.09, 0.16, 1.0)
        GL.glClear(GL.GL_COLOR_BUFFER_BIT)

        # Background + orb
        GL.glUseProgram(self._prog)
        loc_t = GL.glGetUniformLocation(self._prog, "u_t")
        loc_r = GL.glGetUniformLocation(self._prog, "u_res")
        GL.glUniform1f(loc_t, self.t)
        GL.glUniform2f(loc_r, float(max(w, 1)), float(max(h, 1)))
        loc = GL.glGetAttribLocation(self._prog, "a_pos")
        GL.glBindBuffer(GL.GL_ARRAY_BUFFER, self._vbo)
        GL.glEnableVertexAttribArray(loc)
        GL.glVertexAttribPointer(loc, 2, GL.GL_FLOAT, False, 0, None)
        GL.glDrawArrays(GL.GL_TRIANGLES, 0, 6)
        GL.glDisableVertexAttribArray(loc)

        # Text overlay
        GL.glEnable(GL.GL_BLEND)
        GL.glBlendFunc(GL.GL_SRC_ALPHA, GL.GL_ONE_MINUS_SRC_ALPHA)
        GL.glUseProgram(self._text_prog)
        GL.glActiveTexture(GL.GL_TEXTURE0)
        GL.glBindTexture(GL.GL_TEXTURE_2D, self._text_tex)
        GL.glUniform1i(GL.glGetUniformLocation(self._text_prog, "u_tex"), 0)
        GL.glBindBuffer(GL.GL_ARRAY_BUFFER, self._text_vbo)
        loc_p = GL.glGetAttribLocation(self._text_prog, "a_pos")
        loc_u = GL.glGetAttribLocation(self._text_prog, "a_uv")
        stride = 4 * 4
        GL.glEnableVertexAttribArray(loc_p)
        GL.glVertexAttribPointer(loc_p, 2, GL.GL_FLOAT, False, stride, ctypes.c_void_p(0))
        GL.glEnableVertexAttribArray(loc_u)
        GL.glVertexAttribPointer(loc_u, 2, GL.GL_FLOAT, False, stride, ctypes.c_void_p(8))
        GL.glDrawArrays(GL.GL_TRIANGLES, 0, 6)
        GL.glDisableVertexAttribArray(loc_p)
        GL.glDisableVertexAttribArray(loc_u)
        GL.glDisable(GL.GL_BLEND)

        GL.glFlush()
        return True


def main(argv):
    os.environ.setdefault("GDK_BACKEND", "wayland")
    # Prefer GLES via GTK
    os.environ.setdefault("GSK_RENDERER", "gl")
    app = GlHello()
    return app.run(argv)


if __name__ == "__main__":
    sys.exit(main(sys.argv) or 0)
