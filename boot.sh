#!/bin/sh

set -xe

# TODO: implement more robust imaging
nasm src/boot/stage1.s -fbin -o img/s1.bin -i "src/boot/include"
nasm src/boot/stage2.s -fbin -o img/s2.bin -i "src/boot/include"

gcc -ffreestanding -c src/kern.c -o img/kern.o
ld -o img/kern.bin -Ttext 0x1000 img/kern.o --oformat binary

cat img/s1.bin img/s2.bin img/kern.bin > img/boot.bin


qemu-system-x86_64 \
-enable-kvm \
-m 2048 \
-d int,cpu_reset \
-D log.txt \
-drive format=raw,file=./img/boot.bin
