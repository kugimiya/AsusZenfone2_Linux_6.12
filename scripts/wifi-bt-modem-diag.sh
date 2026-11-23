#!/bin/sh
# Диагностика Wi-Fi / BT / модема на asus-z00e (Nura/pmOS).
# Запуск на телефоне: sh wifi-bt-modem-diag.sh
set -e

SUDO=
if [ "$(id -u)" -ne 0 ]; then
	SUDO="sudo"
fi

section() {
	printf '\n=== %s ===\n' "$1"
}

section "kernel"
uname -a
uptime

section "remoteproc"
for d in /sys/class/remoteproc/remoteproc*; do
	[ -e "$d" ] || continue
	printf '%s name=%s state=%s fw=%s\n' \
		"$d" \
		"$(cat "$d/name" 2>/dev/null || echo '?')" \
		"$(cat "$d/state" 2>/dev/null || echo '?')" \
		"$(cat "$d/firmware" 2>/dev/null || echo '?')"
done

section "firmware_class.path"
cat /sys/module/firmware_class/parameters/path 2>/dev/null || echo '(empty)'

section "wcnss firmware hashes"
for f in wcnss.mdt wcnss.b00 wcnss.b06 wcnss.b11; do
	for p in \
		"/run/msm-firmware-loader/target/$f" \
		"/usr/lib/firmware/$f" \
		"/run/msm-firmware-loader/mnt/modem/image/$f"
	do
		[ -e "$p" ] || continue
		sha256sum "$p" 2>/dev/null || true
	done
done

section "NV"
ls -la /usr/lib/firmware/wlan/prima/ 2>/dev/null || echo 'no prima NV dir'

section "reserved-memory wcnss/mpss"
for n in wcnss mpss@86800000 mba gps venus; do
	p="/sys/firmware/devicetree/base/reserved-memory/$n"
	[ -e "$p" ] || continue
	st=okay
	[ -f "$p/status" ] && st=$(tr -d '\0' <"$p/status")
	printf '%s status=%s\n' "$n" "$st"
done

section "mss / pronto DT status"
for p in \
	/sys/firmware/devicetree/base/soc@0/remoteproc@4080000 \
	/sys/firmware/devicetree/base/soc@0/remoteproc@a204000
do
	[ -e "$p" ] || continue
	st=okay
	[ -f "$p/status" ] && st=$(tr -d '\0' <"$p/status")
	comp=$(tr -d '\0' <"$p/compatible" 2>/dev/null | tr '\0' ' ')
	printf '%s status=%s compatible=%s\n' "$(basename "$p")" "$st" "$comp"
done

section "net / bluetooth"
ip -br link 2>/dev/null || ip link
ls /sys/class/bluetooth 2>/dev/null || echo 'no bluetooth class'

section "loaded wireless modules"
lsmod | grep -iE 'wcn|wlan|btqcom|wcnss|hci|qrtr|rmnet|bam' || echo '(none)'

section "available modules"
modinfo wcn36xx 2>/dev/null | sed -n '1,8p' || echo 'no wcn36xx'
modinfo btqcomsmd 2>/dev/null | sed -n '1,8p' || echo 'no btqcomsmd'

section "dmesg (filtered)"
$SUDO dmesg 2>/dev/null | grep -iE \
	'wcnss|wcn36|wifi|wlan|bluetooth|btqcom|hci|modem|mpss|pas|qcom_scm|remoteproc|iris|firmware wcnss' \
	| tail -n 80 || true

section "packages"
apk info 2>/dev/null | grep -iE \
	'wcnss|firmware-asus|msm-firmware|modem|bluetooth|asus-z00e|rproc' || true
