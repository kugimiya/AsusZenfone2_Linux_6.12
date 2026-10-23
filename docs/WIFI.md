# Wi-Fi: что уже проверено

Симптом один: `qcom_scm_pas_init_image` для PAS id 6 возвращает ошибку, в dmesg это `error -22 initializing firmware wcnss.mdt`. Сырой ответ TrustZone на обычном вызове — `a0 = 0xfffffffe` (`-2`, EINVAL_ARG). `qcom_scm_remap_error` превращает `-2` в `-22`. До `PAS_AUTH_AND_RESET` выполнение не доходит.

Оба файла прошивки отклоняются одинаково:

- `experiments/wcnss-modem-test.mdt` — раздел modem, август 2016, тестовые ключи Qualcomm.
- `experiments/wcnss-system-oem.mdt` — `/system/etc/firmware/wcnss.mdt`, сертификат OEM, OEM_ID `0x0029`. Этим файлом пользовался Android.

Оба ELF32, сегменты залинкованы на `0x8b600000`, у всех load-сегментов стоит бит relocatable. Стоковый Android на этом телефоне отдавал pronto область `0x8bd00000` размером 6 МиБ, а не `0x8b600000`. Адрес `0x8b600000` — требование нерелоцируемой прошивки на L8150, не раскладка этого аппарата.

Сейчас в DTB зарезервировано `0x8b600000–0x8bbfffff`. `PAS_MEM_SETUP` на это окно и на старое окно `0x86800000` возвращает 0 и не меняет ответ `PAS_INIT_IMAGE`. Адрес загрузки не аргумент `PAS_INIT_IMAGE`.

Также проверено и не лечит `-22`:

- выбор файла прошивки и путь `msm-firmware-loader`;
- частота crypto clock 80 МГц против 160 МГц;
- соглашение SCM: два аргумента ARM32 — наименее плохое, три аргумента дают ENOMEM, legacy даёт EIO;
- SHM bridge. На этом MSM8916 2016 года гипервизор сам не требует моста, а буфер, который уже является мостом, вызов ломает.

Опасные пробы, которые не повторять:

- страница `GFP` по физическому адресу вроде `0x85d86000`, подставленная указателем метаданных, повесила TrustZone внутри SMC;
- `mem_setup` по памяти, которую занимает Linux.

Патч `vendor/pmaports/device/testing/linux-postmarketos-qcom-msm8916/0003-qcom-scm-pas-strongly-ordered-metadata.patch` пытается отдать метаданные как Device-nGnRnE. Он вызывается только из `qcom_scm_pas_init_image`. На рабочем ядре USB поднимается из initramfs примерно на 2.8 с, а WCNSS доходит до этого вызова примерно на 24 с. Сборка r9 с этим патчем USB не показала, значит загрузка оборвалась раньше вызова. Лога паники нет. Конфиг r9 отличается от r8 только версией clang (23.1.3 → 23.1.4), бинарно это полная пересборка.

На телефоне для `msm-firmware-loader` уже лежит постоянный drop-in: `/etc/systemd/system/msm-firmware-loader.service.d/mkdir.conf` с `ExecStartPre=/bin/mkdir -p /run/msm-firmware-loader`.
