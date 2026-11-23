#!/bin/bash
# Pack an ANDROID! boot.img for stock aboot `fastboot boot` (appended DTB with IDs).
# Usage: pack-boot-oneshot.sh -k vmlinuz -r initramfs -d dtb -o out.img
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
MKBOOTIMG="$ROOT/vendor/lk2nd/lk2nd/scripts/mkbootimg"
KERNEL= RAMDISK= DTB= OUT=
CMDLINE='quiet splash plymouth.ignore-serial-consoles plymouth.prefer-fbcon earlycon console=ttyMSM0,115200 pmos_boot_uuid=57703427-7442-4a90-b2e4-1e21f1fcdee3 pmos_root_uuid=4f70290a-3772-4bed-a1c0-068b5e6b7873 pmos_rootfsopts=defaults'

while getopts 'k:r:d:o:c:' opt; do
	case "$opt" in
		k) KERNEL=$OPTARG ;;
		r) RAMDISK=$OPTARG ;;
		d) DTB=$OPTARG ;;
		o) OUT=$OPTARG ;;
		c) CMDLINE=$OPTARG ;;
		*) exit 2 ;;
	esac
done
[ -n "$KERNEL" ] && [ -n "$RAMDISK" ] && [ -n "$DTB" ] && [ -n "$OUT" ] || {
	echo "usage: $0 -k vmlinuz -r initramfs -d dtb -o out.img" >&2
	exit 2
}
TMP=$(mktemp)
trap 'rm -f "$TMP"' EXIT
cat "$KERNEL" "$DTB" >"$TMP"
python3 "$MKBOOTIMG" \
	--kernel "$TMP" \
	--ramdisk "$RAMDISK" \
	--cmdline "$CMDLINE" \
	--base 0x80000000 \
	--kernel_offset 0x80000 \
	--ramdisk_offset 0x2000000 \
	--tags_offset 0x1e00000 \
	--pagesize 2048 \
	--header_version 0 \
	-o "$OUT"
ls -la "$OUT"
