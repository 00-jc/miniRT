#!/usr/bin/env python3
import sys, struct, subprocess, glob, os

src = sys.argv[1]
base = os.path.splitext(os.path.basename(src))[0]
base = base.replace('_diff_4k', '').replace('_disp_4k', '').replace('_4k', '')

dst_dir = 'textures'
dst_bmp = os.path.join(dst_dir, base + '.bmp')
dst_clr = os.path.join(dst_dir, base + '.clr')

diff = glob.glob(os.path.join(dst_dir, '*_diff_*'))
disp = glob.glob(os.path.join(dst_dir, '*_disp_*'))

if not disp:
    print('no displacement map found', file=sys.stderr)
    sys.exit(1)
if not diff:
    print('no diffuse map found', file=sys.stderr)
    sys.exit(1)

disp_src = disp[0]
diff_src = diff[0]

dims = subprocess.check_output(['identify', '-format', '%w %h', disp_src]).split()
w, h = int(dims[0]), int(dims[1])

gray = subprocess.check_output(['magick', disp_src, '-colorspace', 'Gray', '-depth', '8', 'gray:-'])
with open(dst_bmp, 'wb') as f:
    f.write(struct.pack('<QQ', w, h))
    f.write(gray)

dims = subprocess.check_output(['identify', '-format', '%w %h', diff_src]).split()
w, h = int(dims[0]), int(dims[1])

rgba = subprocess.check_output(['magick', diff_src, '-depth', '8', 'rgba:-'])
with open(dst_clr, 'wb') as f:
    f.write(struct.pack('<QQ', w, h))
    f.write(rgba)

for pat in ['textures/*.jpg', 'textures/*.png', 'textures/*.exr', '*.blend']:
    for f in glob.glob(pat):
        os.remove(f)

print(f'{dst_bmp} ({os.path.getsize(dst_bmp)} bytes)')
print(f'{dst_clr} ({os.path.getsize(dst_clr)} bytes)')
