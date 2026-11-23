#!/bin/sh
# Post-kiosk recovery/fixups (run as root over SSH/USB).
set -eu
addgroup user video 2>/dev/null || true
addgroup user seat 2>/dev/null || true
if command -v nmcli >/dev/null; then
  nmcli radio wifi on || true
  for uuid in $(nmcli -t -f UUID,TYPE connection show | awk -F: '$2=="802-11-wireless"{print $1}'); do
    nmcli connection modify "$uuid" connection.permissions "" || true
    nmcli connection modify "$uuid" connection.autoconnect yes || true
    nmcli connection up "$uuid" || true
  done
fi
# Prefer seatd if logind seats fail for cage
if ! pgrep -x cage >/dev/null; then
  echo "cage not running; last tinydm log:"
  journalctl -u tinydm -b --no-pager | tail -40 || true
fi
systemctl restart seatd tinydm || true
echo "tinydm=$(systemctl is-active tinydm) seatd=$(systemctl is-active seatd)"
ps w | grep -E 'cage|hello|presenter' | grep -v grep || true
free -m | head -2
