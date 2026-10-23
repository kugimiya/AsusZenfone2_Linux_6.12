# Откуда взяты вложенные деревья

Снимок снят 23 октября 2026. Каталоги `.git` внутрь этого репозитория не копировались: история апстрима остаётся у исходных remote, а локальные правки лежат прямо в `vendor/`. Отдельные diff — в `docs/diffs/`.

| Каталог | Remote | Коммит | Локальные правки |
| --- | --- | --- | --- |
| `vendor/lk2nd` | https://github.com/msm8916-mainline/lk2nd.git | `fd380ac637d1af38598e3f3c5321d4c962b96315` (`main`) | `lk2nd/device/dts/msm8916/msm8916-asus-z00e.dts`: board-id 24 и соседние id, чтобы стоковый aboot нашёл DTB |
| `vendor/pmaports` | https://gitlab.postmarketos.org/postmarketOS/pmaports.git | `ed54e99086dcc39a2575f658d7be59904e155252` (`main`) | пакеты `device-asus-z00e`, `firmware-asus-z00e`, патчи `0002` и `0003`, правка `APKBUILD` и конфигов ядра |
| `vendor/pmbootstrap` | https://gitlab.postmarketos.org/postmarketOS/pmbootstrap.git | `ff954a63c7a5ead5045150f5a79f035259512df2` (`main`) | нет |
| `vendor/lmdpdg` | https://github.com/msm8916-mainline/linux-mdss-dsi-panel-driver-generator.git | `28c4df25628f6241ce925af15637a443ea2b3bb5` (`master`) | нет |

Живая копия, из которой собран этот снимок, остаётся в `/home/kugichka/src/z00ed-pmos`.

Демо-ключи OpenSSL из `vendor/lk2nd/lib/openssl` и `vendor/pmaports/device/archived/linux-xiaomi-latte/MOK.key` в git не входят. Сборка lk2nd их не использует, а GitHub push protection не принимает `rsa8192.pem`. На диске файлы остаются.
