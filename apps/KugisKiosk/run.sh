#!/bin/sh
# KugisKiosk launcher for Cage (also works under Phosh).
set -eu
APP_DIR="$(CDPATH= cd -- "$(dirname "$0")" && pwd)"
cd "$APP_DIR"

UID_NUM="$(id -u)"
export XDG_RUNTIME_DIR="${XDG_RUNTIME_DIR:-/run/user/$UID_NUM}"
export WAYLAND_DISPLAY="${WAYLAND_DISPLAY:-wayland-0}"
export DBUS_SESSION_BUS_ADDRESS="${DBUS_SESSION_BUS_ADDRESS:-unix:path=$XDG_RUNTIME_DIR/bus}"
export DISPLAY="${DISPLAY:-:1}"
export GDK_BACKEND="${GDK_BACKEND:-wayland}"
export GSK_RENDERER="${GSK_RENDERER:-gl}"
export HOME="${HOME:-/home/user}"

exec /usr/bin/python3 "$APP_DIR/kugikiosk.py"
