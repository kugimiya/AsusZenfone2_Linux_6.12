#!/bin/sh
# Switch z00e from Phosh/greetd to Cage kiosk + Hello Skia (run as root).
set -eu

APP_DIR="${APP_DIR:-/home/user/apps/hello-skia}"
USER_NAME="${USER_NAME:-user}"

echo "==> packages"
apk add --no-cache \
  postmarketos-ui-cage \
  postmarketos-base-ui-cage \
  tinydm \
  tinydm-systemd \
  cage \
  seatd \
  py3-opengl \
  py3-cairo \
  mesa-egl \
  mesa-gles \
  mesa-dri-gallium \
  font-dejavu

# seatd has no systemd unit on Alpine edge sometimes — provide one
if [ ! -f /etc/systemd/system/seatd.service ]; then
  cat >/etc/systemd/system/seatd.service <<'EOF'
[Unit]
Description=Seat management daemon
Before=tinydm.service greetd.service display-manager.service

[Service]
Type=simple
ExecStart=/usr/bin/seatd -g video
Restart=always
RestartSec=1

[Install]
WantedBy=multi-user.target
EOF
fi

mkdir -p /etc/cage-ui
cat >/etc/cage-ui/10-hello-skia.sh <<EOF
# Kiosk command for cage-ui-session.sh
CAGE_UI_COMMAND="$APP_DIR/run.sh"
export CAGE_UI_COMMAND
export HELLO_SKIA_BACKEND=gles
export HELLO_SKIA_TAP_QUIT=0
# Prefer logind; fall back to seatd if present
export LIBSEAT_BACKEND="\${LIBSEAT_BACKEND:-logind}"
export XDG_RUNTIME_DIR="/run/user/10000"
EOF

# Performance: CPU already performance via tuned; pin GPU
mkdir -p /etc/tmpfiles.d
cat >/etc/tmpfiles.d/z00e-perf.conf <<'EOF'
w /sys/class/devfreq/1c00000.gpu/governor - - - - performance
w /sys/devices/system/cpu/cpufreq/policy0/scaling_governor - - - - performance
EOF

# tinydm session → cage
if command -v tinydm-set-session >/dev/null; then
  tinydm-set-session -s /usr/share/wayland-sessions/cage-ui.desktop
fi

# Switch display manager: greetd/phrog → tinydm (autologin uid 10000)
systemctl enable seatd.service || true
systemctl disable greetd.service 2>/dev/null || true
systemctl disable phrog.service 2>/dev/null || true
# display-manager alias
rm -f /etc/systemd/system/display-manager.service
systemctl enable tinydm.service
ln -sf /usr/lib/systemd/system/tinydm.service /etc/systemd/system/display-manager.service

# Debloat: stop user-facing phone/GNOME cruft (keep NetworkManager, audio, ssh)
echo "==> disable heavy user services (best-effort)"
for u in \
  chatty \
  firefox \
  gnome-software \
  flatpak-system-helper
 do
  systemctl disable --now "$u" 2>/dev/null || true
done

# Mask noisy session services that pull themselves in under GNOME (harmless under cage)
mkdir -p /etc/systemd/user
for u in \
  mobi.phosh.OSK.service \
  org.gnome.SettingsDaemon.PrintNotifications.service \
  org.gnome.SettingsDaemon.Sharing.service \
  org.gnome.SettingsDaemon.Smartcard.service \
  org.gnome.SettingsDaemon.Wacom.service
 do
  systemctl --global mask "$u" 2>/dev/null || true
done

echo "==> apk del optional apps (keep failing soft)"
# Do not remove postmarketos-ui-phosh yet — may share deps; remove leaf apps
apk del --no-cache \
  firefox-esr \
  flatpak \
  gnome-software \
  gnome-software-plugin-apk2 \
  gnome-software-plugin-flatpak \
  gnome-maps \
  gnome-weather \
  gnome-calendar \
  gnome-contacts \
  gnome-calculator \
  gnome-clocks \
  gnome-text-editor \
  chatty \
  gnome-calls \
  calls \
  phosh-mobile-settings \
  postmarketos-ui-phosh-default-osk \
  2>/dev/null || true

chmod +x "$APP_DIR/run.sh" "$APP_DIR/presenter_gl.py" "$APP_DIR/presenter.py" 2>/dev/null || true
chown -R "$USER_NAME:$USER_NAME" "$APP_DIR" 2>/dev/null || true

# DRM access for Cage/seatd
addgroup "$USER_NAME" video 2>/dev/null || true
addgroup "$USER_NAME" seat 2>/dev/null || true

# Ensure Wi-Fi keeps working without a Phosh session: promote NM connections to system
if command -v nmcli >/dev/null 2>&1; then
  for uuid in $(nmcli -t -f UUID,TYPE connection show | awk -F: '$2=="802-11-wireless"{print $1}'); do
    nmcli connection modify "$uuid" connection.permissions "" 2>/dev/null || true
    nmcli connection modify "$uuid" connection.autoconnect yes 2>/dev/null || true
  done
fi

# If Cage dies in a loop, still leave SSH reachable via multi-user.target
systemctl enable sshd 2>/dev/null || systemctl enable ssh 2>/dev/null || true

systemd-tmpfiles --create /etc/tmpfiles.d/z00e-perf.conf 2>/dev/null || true

echo "==> done. Reboot to enter Cage kiosk."
echo "    SSH remains on :22. Rollback: enable greetd, tinydm-set-session phosh.desktop"
