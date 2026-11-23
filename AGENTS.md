# Правила работы с этим телефоном

Устройство одно: ASUS Zenfone 2 Laser ZE500KL (`ASUS_Z00ED`, плата `ASUS_Z00E_2`). Это не Z00L и не Z00T. Чужие платы, GPIO и регуляторы оттуда не копировать.

Сейчас на нём Linux: **Nura edge** (Alpine/postmarketOS), hostname `z00e`, ядро `6.12.1-msm8916 #9`, UI — **Phosh + phoc** (Wayland `wayland-0`, XWayland `:1`). Экран 720×1280. Пользователь сессии `user` (uid `10000`).

## Как попасть на устройство

- ADB, когда телефон ещё на Android: `adb -s 138f09fb`. Другие устройства по ADB не трогать.
- Linux по USB-сети: телефон `172.16.42.1`, хост `172.16.42.2`. Имя интерфейса `enx…` меняется каждый раз. Логин `user`, пароль `1234`, sudo тем же паролем. `dmesg` только через sudo.
- Пинг на `172.16.42.1` без привязки к USB-интерфейсу уходит в VPN `happ-xray`. Проверять `ip route get 172.16.42.1` и пинговать с `-I enx…` / `-b 172.16.42.2` у SSH.
- USB-гаджет Linux раньше был `18d1:d001`. На текущей Nura в режиме tethering/NCM встречается `1d6b:0103` (Linux Foundation NCM) и интерфейс `enx…`. Fastboot — `18d1:d00d`. Ни `18d1:d001`, ни `1d6b:0103` не считать fastboot.
- В UI USB есть режимы вроде Developer / tethering; для сети нужен **data-кабель**. Зарядный-only в `lsusb` телефона не показывает. После смены режима полезно переткнуть кабель.
- NetworkManager на хосте часто вешает на `enx…` только link-local `169.254…/16` (`ipv4.method=link-local`). Тогда вручную: `ip addr add 172.16.42.2/24 dev enx…`. На телефоне адрес `usb0` = `172.16.42.1/16`.
- У телефона по умолчанию нет маршрута в интернет (только USB). Для `apk`/`npm`: на хосте IP forward + MASQUERADE с `172.16.42.0/24` в uplink (у нас уходил в `happ-xray`), на телефоне `ip route replace default via 172.16.42.2` и DNS через `resolvectl dns usb0 1.1.1.1`.
- GUI с SSH: `XDG_RUNTIME_DIR=/run/user/10000`, `WAYLAND_DISPLAY=wayland-0`, `DBUS_SESSION_BUS_ADDRESS=unix:path=/run/user/10000/bus`, `DISPLAY=:1`. Скриншот: `grim`.

## Два разных fastboot

| Кто | Серийник | `getvar product` |
| --- | --- | --- |
| Стоковый aboot | `G2AZCY07A029` | `MSM8916` |
| lk2nd | `138f09fb` | `lk2nd-msm8916` |

Перед любой записью прочитать серийник и product. `fastboot getvar` по неверному серийнику зависает: такие процессы убивать до настоящей прошивки.

`reboot bootloader` из Linux попадает в стоковый aboot, не в lk2nd. При холодном включении с зажатой кнопкой: **Vol Up → fastboot**, **Vol Down → TWRP** (recovery `mmcblk0p35`). Без кнопок — обычная загрузка Linux через lk2nd/extlinux. У lk2nd нет таймаута extlinux: неизвестные строки пропускаются, сразу грузится метка `default`.

## Что нельзя прошивать

- Из стокового aboot нельзя делать `fastboot flash boot` образом Linux. Это затирает lk2nd, потому что он лежит в первых 512 КиБ раздела boot, а Linux — сразу за ним.
- `fastboot boot` из стокового aboot допустим только для образа, в чьём DTB есть `qcom,msm-id` и `qcom,board-id` этого аппарата. Готовый такой образ, если он собран локально: `images/boot-z00e-bms-ids.img` (в git не хранится, сумма в `docs/SHA256SUMS`). Он грузит рабочее ядро в память и раздел не пишет.
- Recovery не прошивать. TWRP нужен для отката на Android.
- `images/boot-lineage.img` — локальная копия старого Android-ядра, в git её нет. Она снимает lk2nd. Не писать её, пока об этом прямо не попросили.
- Раздел system не трогать.
- Не включать зарядку `qcom,pm8916-lbc`: стоковая схема её запрещает, драйвер при пробе пишет CHG_EN. SMB358 тоже не включать без отдельной задачи: драйвер переписывает регистры зарядки.

## Как обновляется уже стоящая система

Грузится extlinux с раздела boot: `/boot/vmlinuz`, `/boot/msm8916-asus-z00e.dtb`, `/boot/initramfs`. Образ Android внутри раздела boot при этом не используется. Новое ядро класть отдельным файлом и менять метку `default` только после того, как оно само подняло USB.

Модули initramfs и `/lib/modules/6.12.1-msm8916` собраны вместе с ядром `#9` (clang 23.1.3). `CONFIG_MODVERSIONS` выключен, `CONFIG_MODULE_ALLOW_BTF_MISMATCH` тоже. Чужое ядро с тем же `uname -r`, но другой сборкой BTF, эти модули не примет, и initramfs не поднимет USB-гаджет. Ядро r9 так и осталось непроверенным: USB не появился, pstore пуст, ramoops в дереве нет.

## Wi-Fi

Рабочий набор — **Android `system` `/etc/firmware/wcnss.*`**, не modem/`msm-firmware-loader`. Modem-сборка даёт `PAS_INIT_IMAGE` `-22`. На устройстве: файлы в `/usr/lib/firmware/wcnss.*` + `z00e-wcnss-fw.service` (очищает `firmware_class.path`). Копия в репо: `firmware/wcnss-android-system/`.

Не повторять `lowbounce` / `mem_setup` по RAM Linux. Подробности и опровергнутые гипотезы — `docs/WIFI.md`.

## Графика и приложения на Phosh

- GPU — Adreno 306 (freedreno GL/GLES/EGL есть). **Vulkan на железе нет** (Turnip только a6xx+). `mesa-vulkan-swrast` (lavapipe) ставится, но нативному `Window` из `skia-canvas` этого мало: «No suitable physical device found».
- Hello World на Node+Skia: репозиторий `apps/hello-skia/`, на телефоне `~/apps/hello-skia/`. Рисование — `skia-canvas` (CPU), окно — GTK4 Wayland (`presenter.py`). Лончер: `eco.nura.HelloSkia.desktop`.
- У Phosh **app-id окна должен совпадать с basename `.desktop`** и быть reverse-DNS (`eco.nura.HelloSkia`). Иначе в журнале: `Could not find application for app-id '…'`, окно может не подняться поверх текущего UI. `hello-skia` как GApplication id невалиден (нужна точка). GTK: `app.run(sys.argv)`, не `run(None)`.
- Для GUI из SSH удобнее `gio launch ~/.local/share/applications/eco.nura.HelloSkia.desktop`, чем голый `node` без сессионных переменных.

## Сборка

Ядро для прошивки собирать pmbootstrap/Alpine clang. Системный clang Debian (19) даёт несовместимые модули. Команда, которой собирался пакет: `pmbootstrap -j2 build linux-postmarketos-qcom-msm8916`.

Пакеты на телефоне — через `apk` (edge/Nura mirrors). Node: `apk add nodejs npm`. Нативная `skia-canvas` тянет prebuild `@skia-canvas/linux-arm64-musl`.