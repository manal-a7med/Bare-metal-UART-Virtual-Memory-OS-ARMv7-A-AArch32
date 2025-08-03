CROSS_COMPILE = arm-none-eabi-
CC = $(CROSS_COMPILE)gcc
AS = $(CROSS_COMPILE)as
LD = $(CROSS_COMPILE)ld
OBJCOPY = $(CROSS_COMPILE)objcopy

CFLAGS = -Wall -O2 -nostdlib -nostartfiles -ffreestanding -march=armv7-a -marm -mtune=cortex-a7
LDFLAGS = -T linker.ld -nostdlib

OBJS = start.o uart.o main.o handler.o

all: kernel.img

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.S
	$(AS) -o $@ $<

kernel.elf: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

kernel.img: kernel.elf
	$(OBJCOPY) -O binary $< $@

clean:
	rm -f *.o *.elf *.img

run: kernel.img
	qemu-system-arm -M versatilepb -cpu cortex-a8 -kernel kernel.img -nographic -serial stdio
