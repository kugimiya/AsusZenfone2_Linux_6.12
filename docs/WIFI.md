# Wi-Fi / Bluetooth / модем: статус расследования

## Короткий вердикт

**Wi-Fi и Bluetooth работают**, если грузить **WCNSS с Android `system` (`/etc/firmware/wcnss.*`)**, а не с раздела modem/`msm-firmware-loader`.

На modem-наборе TrustZone отклоняет `PAS_INIT_IMAGE` (PAS id 6) → `error -22`. На system-наборе: `remoteproc0` → `running`, `wcn36xx` поднимает `wlan0`, `btqcomsmd` → `hci0`. Скан сетей через NetworkManager успешен.

Модем (MSS/`mpss`) в DTB по-прежнему **выключен** (отдельная тема / риск EDL).

## Рабочая конфигурация (2026-11-23)

| Компонент | Состояние |
| --- | --- |
| Прошивка | Android system `wcnss.mdt` + `.b00`…`.b11` в `/usr/lib/firmware/` |
| `firmware_class.path` | **пустой** (не `/run/msm-firmware-loader/target`) |
| Сервис | `z00e-wcnss-fw.service` (после `msm-firmware-loader`) |
| `remoteproc0` | `running`, WCNSS Version 1.5 1.2 |
| `wlan0` | up, scan OK (например SSID вокруг телефона видны) |
| `hci0` | powered on |

Копия рабочих блобов: [`firmware/wcnss-android-system/`](../firmware/wcnss-android-system/)  
SHA256 `wcnss.mdt` (system): `c7e793ff6968cc92effaaa1d3b3bdd93e74126a12173133e8968ffcbb4be8bb4`  
SHA256 `wcnss.mdt` (modem): `085da003583d9061b40e80b60ddd6a065f3fe7d651b37540a182bf12e8ac6eb3` — **не использовать** на mainline.

## Почему раньше был `-22`

`msm-firmware-loader` подсовывает modem-образ. Он **байтово другой**, чем `/system/etc/firmware` (в т.ч. другой `wcnss.b06`). Ранний вывод «OEM vs modem одинаково падают» был неверным: «OEM» тогда брали неполный/тот же набор.

ELF обоих наборов линкуется на `0x8b600000` (relocatable). Адрес `wcnss_mem` (`0x8b6…` / `0x8bd…` / dynamic `0x868…`) **не был корневой причиной** `-22` на `PAS_INIT_IMAGE`.

## Что опровергнуто (не повторять как фикс `-22`)

- OEM≠modem без проверки хешей; crypto clk 80/160; SCM ABI; SHM bridge;
- `PAS_MEM_SETUP` до init; **strongly-ordered Device-nGnRnE** (`0003`, `#11`: allocator ok, SMC всё равно `-22` на modem-fw);
- pin `wcnss_mem` @ `0x8bd00000` как единственный фикс;
- `lowbounce` / `mem_setup` по RAM Linux.

## Новые стратегии (после SO) — итог

| # | Стратегия | Результат |
| --- | --- | --- |
| E | Сверить ELF load vs mem region | FW @ `0x8b600000`, relocatable; stock CMA был `0x8bd…` |
| F | **Android system vs modem blobs** | **F сработал** |
| G | Metadata phys / XPU | отложено (не нужно при system-fw) |
| H | Iris/XO до PAS | отложено |
| I | Z00L DT diff | низкий приоритет |
| J | Включать mpss | не делать без отдельной задачи |

Дальше по желанию: упаковать system-WCNSS в `firmware-asus-z00e`, поправить MAC/`02:00:…` через NV, проверить соединение (не только scan).

## Автономный контур oneshot

`scripts/fastboot-oneshot-test.sh`, `scripts/pack-boot-oneshot.sh`. Vol Up=fastboot, Vol Down=TWRP. Default extlinux — `#9`.

## Диагностика

`scripts/wifi-bt-modem-diag.sh` / `/usr/local/bin/wifi-bt-modem-diag.sh`.
