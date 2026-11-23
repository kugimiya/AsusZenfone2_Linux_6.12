#!/bin/sh
# Modem-partition wcnss.* -> PAS -22. Prefer Android system blobs.
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

# Restart WCNSS (a204000), not MSS (4080000)
for r in /sys/class/remoteproc/remoteproc*; do
  [ -e "$r/name" ] || continue
  name=$(cat "$r/name" 2>/dev/null || true)
  case "$name" in
    *a204000*|*wcnss*)
      st=$(cat "$r/state" 2>/dev/null || true)
      case "$st" in
        offline|crashed)
          echo stop > "$r/state" 2>/dev/null || true
          sleep 1
          echo start > "$r/state" 2>/dev/null || true
          ;;
      esac
      ;;
  esac
done
