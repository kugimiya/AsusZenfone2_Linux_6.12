#!/bin/sh
# Start MSS remoteproc once firmware links exist (needed for QDSP6 audio).
/usr/local/sbin/z00e-modem-fw-link.sh
for i in 1 2 3 4 5 6 7 8 9 10; do
  for r in /sys/class/remoteproc/remoteproc*; do
    name=$(cat "$r/name" 2>/dev/null) || continue
    case "$name" in
      *4080000*)
        state=$(cat "$r/state")
        if [ "$state" = offline ]; then
          echo start > "$r/state" || true
        fi
        exit 0
        ;;
    esac
  done
  sleep 1
done
