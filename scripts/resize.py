#!/usr/bin/env python3
import glob, struct, subprocess, os, sys

size = int(sys.argv[1]) if len(sys.argv) > 1 else 1024
if size & (size - 1):
    print(f'error: size must be power of 2, got {size}')
    sys.exit(1)

def next_pow2(n):
    return 1 << (n - 1).bit_length()

for path in glob.glob('textures/*.bmp') + glob.glob('textures/*.clr'):
    with open(path, 'rb') as f:
        w, h = struct.unpack('<QQ', f.read(16))
        data = f.read()
    nw = min(next_pow2(w), size)
    nh = min(next_pow2(h), size)
    if w == nw and h == nh:
        print(f'{path}: already {w}x{h}, skipping')
        continue
    is_color = path.endswith('.clr')
    tmp = path + '.tmp'
    with open(tmp, 'wb') as f:
        f.write(data)
    if is_color:
        raw = subprocess.check_output([
            'magick', '-size', f'{w}x{h}', '-depth', '8', f'rgba:{tmp}',
            '-resize', f'{nw}x{nh}!', 'rgba:-'
        ])
    else:
        raw = subprocess.check_output([
            'magick', '-size', f'{w}x{h}', '-depth', '8', f'gray:{tmp}',
            '-resize', f'{nw}x{nh}!', 'gray:-'
        ])
    os.remove(tmp)
    with open(path, 'wb') as f:
        f.write(struct.pack('<QQ', nw, nh))
        f.write(raw)
    print(f'{path}: {w}x{h} -> {nw}x{nh} ({os.path.getsize(path)} bytes)')
