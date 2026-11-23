/**
 * Hello World kiosk app for z00e.
 *
 * Default: GPU path — GTK4 GLArea / OpenGL ES on Freedreno (Adreno 306).
 * skia-canvas Window/GPU needs Vulkan (unavailable here). Optional CPU Skia
 * path: HELLO_SKIA_BACKEND=skia-cpu
 */
import { spawn } from 'node:child_process'
import { dirname, join } from 'node:path'
import { fileURLToPath } from 'node:url'

const __dirname = dirname(fileURLToPath(import.meta.url))
const backend = (process.env.HELLO_SKIA_BACKEND || 'gles').toLowerCase()

function runPresenter(script, extraEnv = {}) {
  const child = spawn('python3', [join(__dirname, script)], {
    stdio: ['pipe', 'inherit', 'inherit'],
    env: {
      ...process.env,
      GDK_BACKEND: 'wayland',
      ...extraEnv,
    },
  })

  const quit = (code = 0) => {
    try {
      child.stdin.end()
    } catch {
      /* ignore */
    }
    child.kill('SIGTERM')
    setTimeout(() => process.exit(code), 50)
  }

  child.on('exit', (code) => process.exit(code ?? 0))
  child.on('error', (err) => {
    console.error('presenter failed:', err)
    quit(1)
  })
  process.on('SIGINT', () => quit(0))
  process.on('SIGTERM', () => quit(0))
  return child
}

if (backend === 'skia-cpu' || backend === 'skia') {
  // Legacy CPU Skia → MemoryTexture presenter
  const { Canvas } = await import('skia-canvas')
  const W = 720
  const H = 1280
  const canvas = new Canvas(W, H, { gpu: false })
  const ctx = canvas.getContext('2d')
  const presenter = runPresenter('presenter.py')

  let frame = 0
  let stopping = false
  const stop = () => {
    stopping = true
    clearInterval(timer)
  }
  presenter.on('exit', stop)

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
    ctx.fillText('skia-canvas CPU fallback', W / 2, H * 0.42 + 70)
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

  const timer = setInterval(() => {
    pushFrame().catch((err) => {
      console.error(err)
      process.exit(1)
    })
  }, 50)
  pushFrame().catch(console.error)
} else {
  console.error('hello-skia: starting GLES presenter (Adreno/Freedreno)')
  runPresenter('presenter_gl.py', {
    GSK_RENDERER: process.env.GSK_RENDERER || 'gl',
    HELLO_SKIA_TAP_QUIT: process.env.HELLO_SKIA_TAP_QUIT || '0',
  })
}
