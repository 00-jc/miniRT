#!/usr/bin/env python3
import glob, struct, subprocess, os, sys

size = int(sys.argv[1]) if len(sys.argv) > 1 else 1024

for path in glob.glob('textures/*.bmp') + glob.glob('textures/*.clr'):
    with open(path, 'rb') as f:
        w, h = struct.unpack('<QQ', f.read(16))
        data = f.read()
    if w <= size and h <= size:
        print(f'{path}: already {w}x{h}, skipping')
        continue
    is_color = path.endswith('.clr')
    tmp = path + '.tmp'
    with open(tmp, 'wb') as f:
        f.write(data)
    if is_color:
        raw = subprocess.check_output([
            'magick', '-size', f'{w}x{h}', '-depth', '8', f'rgba:{tmp}',
            '-resize', f'{size}x{size}!', 'rgba:-'
        ])
    else:
        raw = subprocess.check_output([
            'magick', '-size', f'{w}x{h}', '-depth', '8', f'gray:{tmp}',
            '-resize', f'{size}x{size}!', 'gray:-'
        ])
    os.remove(tmp)
    with open(path, 'wb') as f:
        f.write(struct.pack('<QQ', size, size))
        f.write(raw)
    print(f'{path}: {w}x{h} -> {size}x{size} ({os.path.getsize(path)} bytes)')
