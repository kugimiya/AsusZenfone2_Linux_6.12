#!/bin/sh
# Пересобрать lk2nd для этого ZE500KL. Прошивку скрипт не делает.
set -eu
root=$(CDPATH= cd -- "$(dirname "$0")/.." && pwd)
make -C "$root/vendor/lk2nd" -j4 TOOLCHAIN_PREFIX=arm-none-eabi- lk2nd-msm8916
echo "Образ: $root/vendor/lk2nd/build-lk2nd-msm8916/lk2nd.img"
echo "Каталог сборки в git не входит."
