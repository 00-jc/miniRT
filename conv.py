#!/usr/bin/env python3
import sys, struct, subprocess

src = sys.argv[1]
dst = sys.argv[2]

dims = subprocess.check_output(['identify', '-format', '%w %h', src]).split()
w, h = int(dims[0]), int(dims[1])
pixels = subprocess.check_output(['magick', 'convert', src, '-colorspace', 'Gray', '-depth', '8', 'gray:-'])

with open(dst, 'wb') as f:
    f.write(struct.pack('<QQ', w, h))
    f.write(pixels)
