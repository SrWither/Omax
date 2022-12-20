#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/omax.kernel isodir/boot/omax.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "omax" {
	multiboot /boot/omax.kernel
}
EOF
grub-mkrescue -o omax.iso isodir