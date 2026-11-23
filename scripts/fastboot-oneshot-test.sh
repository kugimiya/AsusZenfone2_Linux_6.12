#!/bin/bash
# Autonomous one-shot: SSH #9 → reboot bootloader (stock aboot) → fastboot boot IMAGE →
# poll USB/SSH → run Wi-Fi diag → reboot back to #9 (or rescue via bms-ids).
#
# Usage:
#   scripts/fastboot-oneshot-test.sh images/boot-z00e-scm-oneshot.img
# Env:
#   SSH_PASS (default 1234), PHONE_IP (172.16.42.1), HOST_IP (172.16.42.2)
#   STOCK_SERIAL (G2AZCY07A029), RESCUE_IMG (images/boot-z00e-bms-ids.img)
#   BOOT_TIMEOUT_S (120), SSH_TIMEOUT_S (90)
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
IMAGE="${1:-}"
if [ -z "$IMAGE" ] || [ ! -f "$IMAGE" ]; then
	echo "usage: $0 <boot.img>" >&2
	exit 2
fi
IMAGE="$(readlink -f "$IMAGE")"

SSH_PASS="${SSH_PASS:-1234}"
PHONE_IP="${PHONE_IP:-172.16.42.1}"
HOST_IP="${HOST_IP:-172.16.42.2}"
STOCK_SERIAL="${STOCK_SERIAL:-G2AZCY07A029}"
RESCUE_IMG="${RESCUE_IMG:-$ROOT/images/boot-z00e-bms-ids.img}"
BOOT_TIMEOUT_S="${BOOT_TIMEOUT_S:-120}"
SSH_TIMEOUT_S="${SSH_TIMEOUT_S:-90}"
export SSHPASS="$SSH_PASS"

SSH_BASE=(sshpass -e ssh
	-o PreferredAuthentications=password
	-o PubkeyAuthentication=no
	-o StrictHostKeyChecking=no
	-o UserKnownHostsFile=/dev/null
	-o ConnectTimeout=5
)

log() { printf '[%s] %s\n' "$(date +%H:%M:%S)" "$*"; }

find_ncm_iface() {
	local c drv
	for c in /sys/class/net/enx*; do
		[ -e "$c" ] || continue
		drv=$(readlink -f "$c/device/driver" 2>/dev/null || true)
		case "$drv" in
			*ipheth*) continue ;;
			*cdc_ncm*|*cdc_ether*|*rndis*) basename "$c"; return 0 ;;
		esac
		# gadget often cdc_ncm; accept non-ipheth enx that is UP
		if [ "$(cat "$c/operstate" 2>/dev/null)" = up ]; then
			basename "$c"
			return 0
		fi
	done
	return 1
}

prepare_iface() {
	local iface="$1"
	sudo ip link set "$iface" up 2>/dev/null || true
	ip addr show "$iface" | grep -q "$HOST_IP" || \
		sudo ip addr add "$HOST_IP/24" dev "$iface" 2>/dev/null || true
	# drop conflicting addr from other enx (e.g. iphone)
	local o
	for o in /sys/class/net/enx*; do
		[ -e "$o" ] || continue
		o=$(basename "$o")
		[ "$o" = "$iface" ] && continue
		sudo ip addr del "$HOST_IP/24" dev "$o" 2>/dev/null || true
	done
}

ssh_phone() {
	local iface
	iface=$(find_ncm_iface) || return 1
	prepare_iface "$iface"
	"${SSH_BASE[@]}" -o BindInterface="$iface" "user@$PHONE_IP" "$@"
}

wait_ssh() {
	local deadline=$((SECONDS + SSH_TIMEOUT_S))
	while [ "$SECONDS" -lt "$deadline" ]; do
		if ssh_phone 'uname -a' 2>/dev/null; then
			return 0
		fi
		sleep 2
	done
	return 1
}

wait_fastboot_stock() {
	local deadline=$((SECONDS + BOOT_TIMEOUT_S))
	local line ser
	while [ "$SECONDS" -lt "$deadline" ]; do
		if lsusb 2>/dev/null | grep -q '18d1:d00d'; then
			line=$(fastboot devices 2>/dev/null | awk 'NF{print; exit}')
			ser=$(echo "$line" | awk '{print $1}')
			if [ "$ser" = "$STOCK_SERIAL" ]; then
				log "fastboot stock $STOCK_SERIAL"
				# verify product without hanging forever
				timeout 8 fastboot -s "$STOCK_SERIAL" getvar product 2>&1 | tee /tmp/z00e-fb-product.txt || true
				grep -qi 'MSM8916' /tmp/z00e-fb-product.txt && return 0
				log "warn: product check failed, continuing with serial match"
				return 0
			fi
			if [ -n "$ser" ] && [ "$ser" != "$STOCK_SERIAL" ]; then
				log "wrong fastboot serial=$ser (want $STOCK_SERIAL); not using"
			fi
		fi
		sleep 2
	done
	return 1
}

wait_usb_after_boot() {
	local deadline=$((SECONDS + SSH_TIMEOUT_S))
	while [ "$SECONDS" -lt "$deadline" ]; do
		if lsusb 2>/dev/null | grep -qE '1d6b:0103|18d1:d001'; then
			if iface=$(find_ncm_iface); then
				prepare_iface "$iface"
				if ping -c1 -W1 -I "$iface" "$PHONE_IP" >/dev/null 2>&1; then
					log "USB ping ok via $iface"
					return 0
				fi
			fi
		fi
		# still in fastboot? boot may have failed
		if lsusb 2>/dev/null | grep -q '18d1:d00d'; then
			log "still in fastboot after boot attempt"
		fi
		sleep 2
	done
	return 1
}

diag_wifi() {
	ssh_phone 'echo 1234 | sudo -S -p "" sh -c "
set +e
echo === uname ===
uname -a
echo === remoteproc ===
for d in /sys/class/remoteproc/remoteproc*; do
  [ -e \"\$d\" ] || continue
  echo \"\$d name=\$(cat \$d/name 2>/dev/null) state=\$(cat \$d/state 2>/dev/null) fw=\$(cat \$d/firmware 2>/dev/null)\"
done
echo === dmesg ===
dmesg | grep -iE \"wcnss|qcom-scm|pas_|remoteproc|strongly|nGnRnE|error -22|Booting fw\" | tail -60
echo === net ===
ip -br link
"' || true
}

rescue_or_reboot() {
	if lsusb 2>/dev/null | grep -q '18d1:d00d'; then
		local ser
		ser=$(fastboot devices 2>/dev/null | awk 'NF{print $1; exit}')
		if [ "$ser" = "$STOCK_SERIAL" ] && [ -f "$RESCUE_IMG" ]; then
			log "rescue: fastboot boot $RESCUE_IMG"
			timeout 120 fastboot -s "$STOCK_SERIAL" boot "$RESCUE_IMG"
			wait_usb_after_boot || true
			wait_ssh || true
			return 0
		fi
	fi
	if ssh_phone 'echo 1234 | sudo -S reboot' 2>/dev/null; then
		log "requested reboot to extlinux #9"
		sleep 8
		wait_usb_after_boot || true
		wait_ssh || true
	else
		log "NEED_POWER_CYCLE: no SSH and no stock fastboot; hold none of Vol keys after power"
		return 1
	fi
}

# --- main ---
log "baseline SSH"
if ! wait_ssh; then
	log "no SSH at start"
	exit 1
fi
BASELINE=$(ssh_phone 'uname -a' 2>/dev/null | tail -1)
log "baseline: $BASELINE"

log "reboot bootloader (stock aboot)"
ssh_phone 'echo 1234 | sudo -S reboot bootloader' 2>/dev/null || true

if ! wait_fastboot_stock; then
	log "stock fastboot not seen; abort"
	exit 1
fi

log "fastboot boot $IMAGE (no flash)"
timeout 180 fastboot -s "$STOCK_SERIAL" boot "$IMAGE"

log "waiting for USB/SSH after oneshot"
if ! wait_usb_after_boot || ! wait_ssh; then
	log "FAIL: no USB/SSH after oneshot"
	rescue_or_reboot || true
	exit 1
fi

GOT=$(ssh_phone 'uname -a' 2>/dev/null | tail -1)
log "booted: $GOT"
log "Wi-Fi / PAS diag"
diag_wifi | tee /tmp/z00e-oneshot-diag.txt

# Return to disk #9 so partition default stays healthy
log "rebooting to extlinux default (#9)"
ssh_phone 'echo 1234 | sudo -S reboot' 2>/dev/null || true
sleep 10
wait_usb_after_boot || true
if wait_ssh; then
	log "back on: $(ssh_phone 'uname -a' 2>/dev/null | tail -1)"
	exit 0
fi
log "NEED_POWER_CYCLE after experiment reboot"
exit 1
