#!/usr/bin/env python3
"""Minimal GTK4 Wayland surface for skia-canvas RGBA frames from stdin."""

import gi
import os
import struct
import sys

gi.require_version("Gtk", "4.0")
gi.require_version("Gdk", "4.0")
from gi.repository import Gdk, GLib, Gtk  # noqa: E402


class Presenter(Gtk.Application):
    def __init__(self):
        # Must match desktop file basename (eco.nura.HelloSkia.desktop) for Phosh.
        super().__init__(application_id="eco.nura.HelloSkia")
        self.picture = None
        self.win = None
        self.width = 0
        self.height = 0

    def do_activate(self):
        self.win = Gtk.ApplicationWindow(application=self, title="Hello Skia")
        self.win.set_decorated(False)
        self.win.set_default_size(720, 1280)
        self.picture = Gtk.Picture()
        self.picture.set_content_fit(Gtk.ContentFit.COVER)
        self.win.set_child(self.picture)

        click = Gtk.GestureClick()
        click.connect("pressed", lambda *a: self.quit())
        self.win.add_controller(click)

        key = Gtk.EventControllerKey()
        key.connect("key-pressed", self._on_key)
        self.win.add_controller(key)

        self.win.present()
        self.win.fullscreen()

        GLib.io_add_watch(
            sys.stdin.buffer,
            GLib.IO_IN | GLib.IO_HUP | GLib.IO_ERR,
            self._on_stdin,
        )

    def _on_key(self, _ctrl, keyval, _code, _state):
        if keyval in (Gdk.KEY_Escape, Gdk.KEY_q, Gdk.KEY_Q):
            self.quit()
            return True
        return False

    def _on_stdin(self, _source, condition):
        if condition & (GLib.IO_HUP | GLib.IO_ERR):
            self.quit()
            return False
        header = sys.stdin.buffer.read(8)
        if len(header) < 8:
            self.quit()
            return False
        width, height = struct.unpack("<II", header)
        nbytes = width * height * 4
        data = sys.stdin.buffer.read(nbytes)
        if len(data) < nbytes:
            self.quit()
            return False
        bytes_ = GLib.Bytes.new(data)
        texture = Gdk.MemoryTexture.new(
            width,
            height,
            Gdk.MemoryFormat.R8G8B8A8,
            bytes_,
            width * 4,
        )
        self.picture.set_paintable(texture)
        self.width, self.height = width, height
        return True


def main(argv):
    # Ensure Wayland
    os.environ.setdefault("GDK_BACKEND", "wayland")
    app = Presenter()
    return app.run(argv)


if __name__ == "__main__":
    sys.exit(main(sys.argv) or 0)
