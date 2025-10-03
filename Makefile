# Makefile for Minimaru OS
CC = gcc
LD = ld
ASM = nasm
QEMU = qemu-system-i386
GRUB = grub-mkrescue
XORRISO = xorriso

CFLAGS = -m32 -Wall -fno-pic -fno-stack-protector -nostdlib -ffreestanding -Iinclude
LDFLAGS = -m elf_i386 -T linker.ld
ASMFLAGS = -f elf32

OBJDIR = build
SRCDIR = .
BOOTDIR = $(SRCDIR)/boot
KERNELDIR = $(SRCDIR)/kernel
DRIVERDIR = $(SRCDIR)/drivers
LIBCDIR = $(SRCDIR)/libc
USERDIR = $(SRCDIR)/userspace

OBJECTS = $(OBJDIR)/boot.o \
          $(OBJDIR)/kernel.o \
          $(OBJDIR)/gdt.o \
          $(OBJDIR)/gdt_flush.o \
          $(OBJDIR)/idt.o \
          $(OBJDIR)/idt_flush.o \
          $(OBJDIR)/isr.o \
		  $(OBJDIR)/isr_asm.o \
          $(OBJDIR)/syscall_int.o \
          $(OBJDIR)/paging.o \
          $(OBJDIR)/process.o \
          $(OBJDIR)/syscall.o \
          $(OBJDIR)/screen.o \
          $(OBJDIR)/keyboard.o \
          $(OBJDIR)/timer.o \
          $(OBJDIR)/string.o \
          $(OBJDIR)/memory.o \
          $(OBJDIR)/shell.o \
          $(OBJDIR)/snake.o

.PHONY: all clean run

all: minimaru.iso

$(OBJDIR)/%.o: $(BOOTDIR)/%.asm
	@mkdir -p $(OBJDIR)
	$(ASM) $(ASMFLAGS) $< -o $@

$(OBJDIR)/%.o: $(KERNELDIR)/%.asm
	@mkdir -p $(OBJDIR)
	$(ASM) $(ASMFLAGS) $< -o $@

$(OBJDIR)/%.o: $(KERNELDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(DRIVERDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(LIBCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(USERDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/kernel.bin: $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $^

minimaru.iso: $(OBJDIR)/kernel.bin grub.cfg
	@mkdir -p isodir/boot/grub
	@cp $(OBJDIR)/kernel.bin isodir/boot/
	@cp grub.cfg isodir/boot/grub/
	$(GRUB) -o $@ isodir

clean:
	rm -rf $(OBJDIR) isodir minimaru.iso

run: minimaru.iso
	$(QEMU) -cdrom minimaru.iso -m 128M