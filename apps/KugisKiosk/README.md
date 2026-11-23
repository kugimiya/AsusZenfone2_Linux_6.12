# KugisKiosk

Fullscreen Cage kiosk for ASUS Zenfone 2 Laser (`z00e`).

Reads:

| File | Role |
| --- | --- |
| `~/.kugikiosk.yaml` | layout / colors |
| `~/.kugikiosk.sh` | shell script; stdout lines are drawn |

## Config (`~/.kugikiosk.yaml`)

```yaml
orientation: portrait   # portrait | portrait-flipped | landscape | landscape-flipped
anchor: center          # center | top-left | top-right | bottom-left | bottom-right
font_size: 28
background: "#0f172a"
foreground: "#f8fafc"
border_color: "#38bdf8"
border_radius: 12
padding: 16             # inside bordered [...] boxes
edge_padding: 16        # inset from screen edges
gap: 12
script_interval_seconds: 10   # how often to re-run ~/.kugikiosk.sh
```

The app watches `~/.kugikiosk.yaml` and `~/.kugikiosk.sh`: edit either file and the UI updates (config → restyle + new interval; script → re-run). Missing files are created with defaults.

## Script (`~/.kugikiosk.sh`)

Created automatically with a small `[internal]` demo (hostname / date / uptime). Replace `~/.kugikiosk.sh` with your own checks.

Each stdout line is one row on screen. Wrap a line in `[...]` to draw a rounded border:

```sh
#!/bin/sh
echo "plain line"
echo "[bordered status]"
date "+[%H:%M:%S]"
```

Keys: `R` / `F5` reload, `Esc` / `Q` quit (when not needed in kiosk).

## Install

```sh
# on phone
mkdir -p ~/apps/KugisKiosk
# copy files, then as root:
# update /etc/cage-ui/ to CAGE_UI_COMMAND=/home/user/apps/KugisKiosk/run.sh
sudo apk add py3-yaml py3-gobject3 gtk4.0 py3-cairo font-dejavu
```
