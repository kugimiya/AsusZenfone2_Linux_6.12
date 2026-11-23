#!/bin/sh
T=/run/msm-firmware-loader/target
i=0
while [ ! -e "$T/mba.mbn" ] && [ $i -lt 50 ]; do
  i=$((i+1))
  sleep 0.1
done
for f in mba.mbn modem.mdt; do
  if [ -e "$T/$f" ]; then
    ln -sfn "$T/$f" /lib/firmware/$f
  fi
done
for f in "$T"/modem.b*; do
  [ -e "$f" ] || continue
  ln -sfn "$f" /lib/firmware/$(basename "$f")
done
# Drop loader wcnss symlinks so Android-system /lib/firmware copies win
for f in wcnss.mdt wcnss.b00 wcnss.b01 wcnss.b02 wcnss.b04 wcnss.b06 wcnss.b09 wcnss.b10 wcnss.b11; do
  if [ -L /lib/firmware/$f ] && readlink /lib/firmware/$f | grep -q msm-firmware-loader; then
    rm -f /lib/firmware/$f
  fi
done
