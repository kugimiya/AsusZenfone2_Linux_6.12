# Hello Skia (kiosk)

Node.js hello-world for ASUS Zenfone 2 Laser (`z00e` / Nura edge), meant to run under **Cage**.

| Layer | Tech |
| --- | --- |
| Default render | GTK4 `GLArea` + OpenGL ES on **Freedreno FD307** (GPU) |
| Fallback | `HELLO_SKIA_BACKEND=skia-cpu` → skia-canvas CPU + `presenter.py` |
| Window / session | Cage kiosk (`postmarketos-ui-cage` + tinydm autologin) |

`skia-canvas` native `Window` / `{ gpu: true }` needs **Vulkan**. Adreno 306 has none, so the kiosk path draws the scene with GLES (gradient + orb on GPU; text atlas uploaded once).

## On the phone

```sh
cd ~/apps/hello-skia
./run.sh
```

Env:

- `HELLO_SKIA_BACKEND=gles` (default) or `skia-cpu`
- `HELLO_SKIA_TAP_QUIT=1` to quit on tap (off in kiosk)

Kiosk setup (root): `scripts/z00e-kiosk-setup.sh`

## Rollback to Phosh

```sh
sudo tinydm-set-session -s /usr/share/wayland-sessions/phosh.desktop
sudo systemctl unmask greetd
sudo systemctl enable --now greetd
sudo systemctl disable tinydm
sudo reboot
```
