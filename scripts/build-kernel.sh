#!/bin/sh
# Собрать пакет ядра тем же способом, что и образы r8/r9/r10.
# Нужен pmbootstrap и конфиг config/pmbootstrap.cfg (или ~/.config/pmbootstrap_v3.cfg).
# aports должен быть полным клоном pmaports с remote на gitlab.postmarketos.org
# (рабочий путь: ~/src/z00ed-pmos/pmaports с синхронизированным
# device/testing/linux-postmarketos-qcom-msm8916 из vendor/pmaports).
# Хостовый clang Debian не использовать: модули/BTF — Alpine clang.
set -eu
exec pmbootstrap -j2 build linux-postmarketos-qcom-msm8916
