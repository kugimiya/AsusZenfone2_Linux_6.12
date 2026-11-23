#!/bin/sh
# Modem-partition wcnss.* -> PAS -22. Prefer Android system blobs.
# Install on device as /usr/local/libexec/z00e-wcnss-fw.sh (see docs/WIFI.md).
ANDROID=/usr/lib/firmware
TARGET=/run/msm-firmware-loader/target

printf %s /usr/lib/firmware > /sys/module/firmware_class/parameters/path 2>/dev/null || true

if [ -d "$TARGET" ] && [ -f "$ANDROID/wcnss.mdt" ]; then
	for f in wcnss.mdt wcnss.b00 wcnss.b01 wcnss.b02 wcnss.b04 wcnss.b06 wcnss.b09 wcnss.b10 wcnss.b11; do
		[ -f "$ANDROID/$f" ] || continue
		ln -sfn "$ANDROID/$f" "$TARGET/$f" 2>/dev/null || cp -a "$ANDROID/$f" "$TARGET/$f" 2>/dev/null || true
	done
	ln -sfn wcnss.mdt "$TARGET/wcnss.mbn" 2>/dev/null || true
fi

RPROC=/sys/class/remoteproc/remoteproc0
if [ -e "$RPROC/state" ]; then
	st=$(cat "$RPROC/state" 2>/dev/null || true)
	case "$st" in
		offline|crashed)
			echo stop > "$RPROC/state" 2>/dev/null || true
			sleep 1
			echo start > "$RPROC/state" 2>/dev/null || true
			;;
	esac
fi
