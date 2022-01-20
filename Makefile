QEMU = qemu-system-x86_64
CC = i386-elf-gcc
CFLAGS = -ffreestanding -O2 -Wall -pedantic -Wextra -fno-pic
LD = i386-elf-ld
AS = nasm

DEPS = $(patsubst %.c,${OBJDIR}/%.o,kernel.c io/io.c io/vga.c std/math.c std/vec.c)

OBJDIR = obj
IMGDIR = img

# TODO: do something about make_directories
# it is kind of convoluted
all: make_directories bootdisk.raw

run: all
	${QEMU} \
	-enable-kvm \
	-m 2048 \
	-drive format=raw,file=./img/bootdisk.raw

bootdisk.raw: ${OBJDIR}/stage1.bin ${OBJDIR}/stage2.bin ${OBJDIR}/kernel.bin
	cat $^ > ${IMGDIR}/bootdisk.raw

# Assembly (bootloader) files

${OBJDIR}/%.bin: src/boot/%.s
	${AS} $< -f bin -i "src/boot/include" -o $@

# Kernel files
${OBJDIR}/kernel.bin: ${OBJDIR}/kernel_entry.o ${DEPS}
	${LD} -o $@ -Ttext 0x10000 $^ --oformat binary

${OBJDIR}/%.o: src/kernel/%.c
	${CC} -c $< -o $@ ${CFLAGS}

${OBJDIR}/kernel_entry.o: src/kernel/entry.s
	${AS} $< -f elf -o $@




.PHONY: clean make_directories
clean:
	rm -rf img
	rm -rf obj
make_directories: ${OBJDIR} ${IMGDIR}

${OBJDIR}:
	mkdir -p ${OBJDIR}/{io,std}

${IMGDIR}:
	mkdir -p ${IMGDIR}
