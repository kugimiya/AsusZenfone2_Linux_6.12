# Hello Skia

Node.js hello-world for Phosh on ASUS Zenfone 2 Laser (`z00e` / Nura edge).

| Layer | Tech |
| --- | --- |
| Graphics | [skia-canvas](https://skia-canvas.org) (Skia, CPU) |
| Window | GTK4 Wayland (`presenter.py`) |

`skia-canvas`’s native `Window` needs Vulkan. Adreno 306 has no Vulkan (and lavapipe is rejected by the window path), so frames are drawn with Skia and presented by GTK.

## On the phone

```sh
cd ~/apps/hello-skia
npm install
npm run icon
./run.sh
```

Launcher entry: `~/.local/share/applications/eco.nura.HelloSkia.desktop`  
(App id must be reverse-DNS and match the `.desktop` basename.)

## Host notes

Phone USB net is `172.16.42.1`; host needs `172.16.42.2` on `enx…` (NetworkManager may only give link-local). Internet for `apk`/`npm` was shared via host NAT.
