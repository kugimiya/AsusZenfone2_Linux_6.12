#!/bin/sh
# Собрать пакет ядра тем же способом, что и образы r8/r9.
# Нужен pmbootstrap и конфиг config/pmbootstrap.cfg (или уже настроенный ~/.config/pmbootstrap_v3.cfg).
# Хостовый clang Debian для этой сборки не использовать: модули initramfs собирались Alpine clang.
set -eu
exec pmbootstrap -j2 build linux-postmarketos-qcom-msm8916
