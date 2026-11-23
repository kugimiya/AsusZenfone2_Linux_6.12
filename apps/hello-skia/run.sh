#!/bin/sh
# Launcher for Phosh: inherit session Wayland/DBus when possible.
set -eu
APP_DIR="$(CDPATH= cd -- "$(dirname "$0")" && pwd)"
cd "$APP_DIR"

UID_NUM="$(id -u)"
export XDG_RUNTIME_DIR="${XDG_RUNTIME_DIR:-/run/user/$UID_NUM}"
export WAYLAND_DISPLAY="${WAYLAND_DISPLAY:-wayland-0}"
export DBUS_SESSION_BUS_ADDRESS="${DBUS_SESSION_BUS_ADDRESS:-unix:path=$XDG_RUNTIME_DIR/bus}"
# XWayland fallback if a toolkit needs it
export DISPLAY="${DISPLAY:-:1}"

# Adreno 306 has no Vulkan; skia-canvas Window needs Vulkan via lavapipe.
if [ -z "${VK_ICD_FILENAMES:-}" ]; then
  for icd in /usr/share/vulkan/icd.d/lvp_icd.*.json; do
    if [ -f "$icd" ]; then
      export VK_ICD_FILENAMES="$icd"
      break
    fi
  done
fi

exec /usr/bin/node "$APP_DIR/hello.js"
