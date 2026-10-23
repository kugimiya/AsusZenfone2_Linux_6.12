# Linux на ASUS Zenfone 2 Laser ZE500KL

Снимок работы по установке postmarketOS на конкретный телефон ASUS Zenfone 2 Laser, модель ZE500KL, плата `ASUS_Z00E_2`, код устройства `asus-z00e`. Это mainline-ядро, не Halium. Камера, GPS и модем в эту работу не входили.

Телефон сейчас загружается в эту систему сам. Картинка и тач доведены до пробы драйверов, процент батареи показывается. Wi-Fi нет: TrustZone отвергает прошивку WCNSS.

## Что лежит в репозитории

| Путь | Что это |
| --- | --- |
| `vendor/pmaports` | Дерево pmaports с пакетами `device-asus-z00e`, `firmware-asus-z00e` и патчами ядра |
| `vendor/lk2nd` | Загрузчик lk2nd с board-id этого экземпляра |
| `vendor/pmbootstrap`, `vendor/lmdpdg` | Инструменты, которыми собирались образ и панель |
| `panel/` | Сгенерированные драйверы панелей, рабочая — AUO RM68200 |
| `firmware/` | NV и cfg Wi-Fi, снятые с телефона |
| `stock/dtb-0.dts` | Декомпиляция стокового DTB |
| `images/` | Каталог для готовых образов. Сами `.img` в git не входят, назначение и суммы известных копий — `docs/FLASH.md`, `docs/SHA256SUMS` |
| `kernel/` | Конфиги r8 и r9. Тарбол исходников и apk-пакеты — локальные файлы сборки, в git их нет |
| `scripts/` | `build-kernel.sh` и `build-lk2nd.sh` |
| `experiments/` | Пробы SCM/WCNSS: исходники модулей и оба файла `wcnss.mdt` |
| `notes/compaction/` | Сжатая история сессии |
| `docs/` | Железо, прошивка, Wi-Fi, пины апстрима |
| `config/pmbootstrap.cfg` | Конфиг сборки, `aports` указывает на `vendor/pmaports` в этом каталоге |
| `AGENTS.md` | Правила для следующей сессии: что можно прошивать и чего не трогать |

Живая копия исходников по-прежнему в `/home/kugichka/src/z00ed-pmos`. Этот каталог хранит правки и скрипты сборки. Готовые образы, apk и тарбол ядра остаются на диске и в git не попадают.

## Состояние телефона

- Ядро, которое загружается: `Linux z00e 6.12.1-msm8916 #9`, сборка 22 октября 2026, clang 23.1.3. Пакет `linux-postmarketos-qcom-msm8916-6.12.1-r8` собирается скриптом `scripts/build-kernel.sh`; apk в репозиторий не кладётся.
- На диске телефона рядом лежит непроверенное ядро r9 как `/boot/vmlinuz.scm`. В загрузку по умолчанию оно не стоит.
- Экран: панель AUO RM68200, модуль `panel-asus-z00e-auo-rm68200`.
- Тач: FocalTech FT5x46, устройство ввода создаётся.
- Батарея: `pm8916-bms-vm` и таблица NVT 2400 мА·ч. Зарядный SMB358 на I2C намеренно не включён, линейная зарядка PMIC тоже выключена.
- Wi-Fi: чип WCN3620, `remoteproc` отвечает `-22` на `PAS_INIT_IMAGE`. Подробности в `docs/WIFI.md`.
- Recovery (раздел `mmcblk0p35`) не прошивался, TWRP на месте. Раздел system Android не трогался.

## Сборка

lk2nd:

```sh
make -C vendor/lk2nd -j4 TOOLCHAIN_PREFIX=arm-none-eabi- lk2nd-msm8916
```

Скрипт кладёт новый образ в `vendor/lk2nd/build-lk2nd-msm8916/lk2nd.img`. Копия, которая уже стоит в телефоне, локально называется `images/lk2nd.img` и в git не хранится.

Ядро собирается через pmbootstrap из Alpine, не системным clang хоста. Иначе модули initramfs не совпадут с ядром. Конфиг: `config/pmbootstrap.cfg`. Канал, на котором собран текущий образ, — `systemd-edge`, интерфейс Phosh.
