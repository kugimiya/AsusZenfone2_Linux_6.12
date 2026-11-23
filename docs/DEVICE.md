# Железо этого экземпляра

MSM8916, 4×Cortex-A53, 2 ГиБ ОЗУ, 16 ГиБ eMMC, экран 720×1280. cmdline стокового ядра: `HW_ID=ZE500KL_PREMP`, `PANEL=AUO`.

Панель — AUO RM68200, compatible `asus,z00e-auo-rm68200`. Это не mainline `raydium,rm68200` и не OTM1284A с Z00L. Сброс GPIO 25, активный низкий. Подсветка и DCS `0x51` (максимум 255), и GPIO 21, активный высокий. Тайминги: 720×1280, hfp 53, hbp 64, hsync 4, vbp/vfp 16, vsync 4, 60 Гц, burst, 4 линии, RGB888. Питание `vdd` — PM8916 L8 2.9 В, `vddio` — L6 1.8 В. Размер 62×110 мм.

Тач — FocalTech FT5x46 на I2C `5-0038` (`blsp_i2c5` = `0x78b9000`). Сброс GPIO 12, активный низкий. IRQ GPIO 13, спад. Питание `vcc` L8, `iovcc` L6. В ядре 6.12 compatible `focaltech,ft5x46` добавлен патчем `0002`; чтение model-id `0xBB` сделано необязательным. Проба дала generic ft5x06, байт id `0x31` из регистра `0xA8`.

Карта памяти: `cd-gpios` GPIO 38, активный низкий. Не копировать с Z00L регулятор SD на GPIO 87, MPU6515 по адресу `0x68` и сброс магнитометра GPIO 112.

Кнопки: громкость вверх GPIO 107, активный низкий. Громкость вниз GPIO 117 взята из lk2nd/z00l. USB ID — GPIO 110. При включении: Vol Up → fastboot, Vol Down → TWRP; без зажатых кнопок — Linux.

Батарея: топливомер `qcom,pm8916-bms-vm`, профиль NVT 2400 мА·ч, 25 °C, верх 4.4 В, отсечка 3.4 В. На последнем успешном чтении было 100 % и 4.4568 В, health Over voltage, статус Discharging. Внешнее зарядное — SMB358 на `blsp_i2c6` (`0x78ba000`), адрес I2C `0x6a`, compatible стока `qcom,smb358-charger`, в mainline `summit,smb358`. OTG GPIO 121, INOK GPIO 20. Драйвер зарядки не включён.

Wi-Fi: `wcn36xx`, iris `qcom,wcn3620`. NV: `firmware/WCNSS_qcom_wlan_nv.bin`, 29816 байт. remoteproc `a204000.remoteproc`, прошивка `wcnss.mdt`, PAS id 6, compatible `qcom,pronto-v2-pil`. SCM-соглашение `smc arm 32`. `wcnss_mem` в DT: стоковый адрес `0x8bd00000/6MiB` (раньше пробовали pin `0x8b600000`).

Идентификаторы, которые нужны стоковому aboot и lk2nd: msm-id `(206,0)`, `(248,0)`, `(249,0)`, `(250,0)` и запасные для других SoC, которые уже прописаны в DTS lk2nd. Производственный board-id этого аппарата — 24. Без него aboot отвечал `dtb not found`.

Разделы, которые важны при прошивке: boot `mmcblk0p34` (lk2nd, затем Linux со смещения 512 КиБ), recovery `mmcblk0p35` (TWRP), userdata `mmcblk0p43` (postmarketOS), system `mmcblk0p42` (Android system на месте), modem `mmcblk0p38` (vfat, прошивки).
