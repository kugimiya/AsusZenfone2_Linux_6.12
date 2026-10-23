# Образы и как ими пользоваться

Файлы из таблицы — локальные сборки и снятый раздел boot. В git их нет: `images/*.img`, `kernel/packages/` и тарбол ядра перечислены в `.gitignore`. Контрольные суммы известных копий — `docs/SHA256SUMS`. Новые образы собирают `scripts/build-kernel.sh` и `scripts/build-lk2nd.sh`.

| Файл | Назначение |
| --- | --- |
| `images/lk2nd.img` | lk2nd для этого board-id. Уже записан в начало раздела boot |
| `images/boot-original.img` | Первый Linux boot.img из сборки pmbootstrap, ядро до батареи |
| `images/boot-z00e-bms.img` | То же ядро, DTB уже с батареей. Из стокового aboot сам по себе не стартует: в DTB нет `qcom,board-id` |
| `images/boot-z00e-bms-ids.img` | Тот же образ плюс msm-id и board-id. `fastboot boot` из стокового aboot (`G2AZCY07A029`) поднимает рабочее ядро в память |
| `images/boot-lk2nd-bms.img` | lk2nd, добитый нулями до 512 КиБ, и следом `boot-z00e-bms.img`. Именно это записано в раздел boot командой `fastboot flash boot` из стокового aboot |
| `images/boot-lineage.img` | Снятый до установки Linux раздел boot LineageOS. Возвращает старое Android-ядро и убирает lk2nd |
| `kernel/packages/…-r8.apk` | Ядро `#9`, которое сейчас загружается через extlinux |
| `kernel/packages/…-r9.apk` | Полная пересборка clang 23.1.4 с патчем strongly-ordered metadata. На телефон как `/boot/vmlinuz` ставилось и USB не появился. Сейчас на диске телефона это `/boot/vmlinuz.scm` |

Повседневное обновление ядра и DTB — замена файлов в `/boot` и обычный `reboot`. Extlinux читается раньше, чем Android-образ из раздела boot.

Загрузчик lk2nd сдвигает начало раздела `boot` на 512 КиБ. Поэтому `fastboot flash boot` из lk2nd пишет Linux после lk2nd, а та же команда из стокового aboot пишет с нуля и стирает lk2nd.
