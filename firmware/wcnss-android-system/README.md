# WCNSS firmware from Android system (ZE500KL)

Copied from this phone's Android `system` partition (`/etc/firmware/wcnss.*`).

Modem/`NON-HLOS` `wcnss.*` is a **different** signed build. On mainline it makes
TrustZone `PAS_INIT_IMAGE` return `-22`. These Android system blobs authenticate
and bring up `remoteproc0`, `wlan0`, and `hci0`.

| File | Role |
| --- | --- |
| `wcnss.mdt` | ELF header + packed hash (7260 bytes) |
| `wcnss.b00`…`b11` | split segments |

SHA256(`wcnss.mdt`) = `c7e793ff6968cc92effaaa1d3b3bdd93e74126a12173133e8968ffcbb4be8bb4`

Install to `/usr/lib/firmware/` and clear `firmware_class.path` so
`msm-firmware-loader` modem symlinks are not preferred (see `z00e-wcnss-fw.service`
on the device).
