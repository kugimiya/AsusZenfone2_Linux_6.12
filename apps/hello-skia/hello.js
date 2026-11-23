/**
 * Hello World: graphics via skia-canvas (Skia), window via GTK4 presenter.
 * skia-canvas Window needs Vulkan; Adreno 306 has none, so we present frames
 * over a pipe to presenter.py on Phosh/Wayland.
 */
import { Canvas } from 'skia-canvas'
import { spawn } from 'node:child_process'
import { dirname, join } from 'node:path'
import { fileURLToPath } from 'node:url'

const __dirname = dirname(fileURLToPath(import.meta.url))
const W = 720
const H = 1280

const canvas = new Canvas(W, H, { gpu: false })
const ctx = canvas.getContext('2d')

const presenter = spawn('python3', [join(__dirname, 'presenter.py')], {
  stdio: ['pipe', 'inherit', 'inherit'],
  env: {
    ...process.env,
    GDK_BACKEND: 'wayland',
  },
})

let frame = 0
let stopping = false

function quit(code = 0) {
  if (stopping) return
  stopping = true
  clearInterval(timer)
  try {
    presenter.stdin.end()
  } catch {
    /* ignore */
  }
  presenter.kill('SIGTERM')
  setTimeout(() => process.exit(code), 50)
}

presenter.on('exit', () => quit(0))
presenter.on('error', (err) => {
  console.error('presenter failed:', err)
  quit(1)
})
process.on('SIGINT', () => quit(0))
process.on('SIGTERM', () => quit(0))

function draw(frameNo) {
  const t = frameNo / 40

  const grad = ctx.createLinearGradient(0, 0, 0, H)
  grad.addColorStop(0, '#0f172a')
  grad.addColorStop(1, '#1e293b')
  ctx.fillStyle = grad
  ctx.fillRect(0, 0, W, H)

  const cx = W * 0.5 + Math.cos(t) * 40
  const cy = H * 0.38 + Math.sin(t * 1.3) * 24
  const orb = ctx.createRadialGradient(cx, cy, 10, cx, cy, 180)
  orb.addColorStop(0, 'rgba(56, 189, 248, 0.55)')
  orb.addColorStop(1, 'rgba(56, 189, 248, 0)')
  ctx.fillStyle = orb
  ctx.beginPath()
  ctx.arc(cx, cy, 180, 0, Math.PI * 2)
  ctx.fill()

  ctx.fillStyle = '#f8fafc'
  ctx.textAlign = 'center'
  ctx.textBaseline = 'middle'
  ctx.font = 'bold 64px DejaVu Sans, sans-serif'
  ctx.fillText('Hello, World!', W / 2, H * 0.42)

  ctx.fillStyle = '#94a3b8'
  ctx.font = '28px DejaVu Sans, sans-serif'
  ctx.fillText('skia-canvas on Zenfone 2 Laser', W / 2, H * 0.42 + 70)

  ctx.fillStyle = '#64748b'
  ctx.font = '22px DejaVu Sans, sans-serif'
  ctx.fillText('Phosh · Wayland · aarch64', W / 2, H * 0.42 + 115)

  ctx.fillStyle = '#38bdf8'
  ctx.font = '24px DejaVu Sans, sans-serif'
  ctx.fillText('tap anywhere to close', W / 2, H * 0.82)
}

async function pushFrame() {
  if (stopping || !presenter.stdin.writable) return
  draw(frame++)
  const raw = await canvas.toBuffer('raw')
  const header = Buffer.alloc(8)
  header.writeUInt32LE(W, 0)
  header.writeUInt32LE(H, 4)
  presenter.stdin.write(header)
  presenter.stdin.write(raw)
}

// ~20 fps — enough for hello-world animation on this SoC
const timer = setInterval(() => {
  pushFrame().catch((err) => {
    console.error(err)
    quit(1)
  })
}, 50)

pushFrame().catch((err) => {
  console.error(err)
  quit(1)
})
