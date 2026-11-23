import { Canvas } from 'skia-canvas'
import { writeFileSync, mkdirSync } from 'node:fs'
import { dirname, join } from 'node:path'
import { fileURLToPath } from 'node:url'

const dir = dirname(fileURLToPath(import.meta.url))
const outDir = join(dir, 'icons')
mkdirSync(outDir, { recursive: true })

const size = 256
const canvas = new Canvas(size, size)
const ctx = canvas.getContext('2d')

ctx.fillStyle = '#0f172a'
ctx.beginPath()
ctx.roundRect(0, 0, size, size, 48)
ctx.fill()

const g = ctx.createRadialGradient(128, 100, 10, 128, 120, 120)
g.addColorStop(0, '#7dd3fc')
g.addColorStop(1, '#0284c7')
ctx.fillStyle = g
ctx.beginPath()
ctx.arc(128, 118, 70, 0, Math.PI * 2)
ctx.fill()

ctx.fillStyle = '#f8fafc'
ctx.font = 'bold 72px DejaVu Sans, sans-serif'
ctx.textAlign = 'center'
ctx.textBaseline = 'middle'
ctx.fillText('Hi', 128, 118)

const png = await canvas.toBuffer('png')
writeFileSync(join(outDir, 'hello-skia.png'), png)
console.log('wrote', join(outDir, 'hello-skia.png'))
