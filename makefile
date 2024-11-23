.PHONY: all
all: bootloader kernel linker iso
	@echo Make has completed.

bootloader: boot.asm
	nasm -f elf boot.asm -o boot.o

kernel: kernel.c
	gcc -m32 -fno-pic -c kernel.c -o kernel.o

linker: linker.ld boot.o kernel.o
	ld -m elf_i386 -T linker.ld -o kernel boot.o kernel.o

iso: kernel
	mkdir -p iso/boot/grub

	cp kernel iso/boot/
	cp grub.cfg iso/boot/grub/
	grub-file --is-x86-multiboot iso/boot/kernel
	grub-mkrescue -o my-kernel.iso iso

.PHONY: clean
clean:
	rm -f *.o kernel *.iso