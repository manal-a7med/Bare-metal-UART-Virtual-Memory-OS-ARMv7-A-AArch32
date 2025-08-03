CC=arm-none-eabi-gcc
LD=arm-none-eabi-ld
AS=arm-none-eabi-as
OBJCOPY=arm-none-eabi-objcopy
CFLAGS=-Wall -O2 -nostdlib -nostartfiles -ffreestanding

all: kernel.img

start.o: start.S
	$(AS) start.S -o start.o

uart.o: uart.c uart.h
	$(CC) $(CFLAGS) -c uart.c -o uart.o

print.o: print.c uart.h
	$(CC) $(CFLAGS) -c print.c -o print.o

kernel.elf: start.o uart.o print.o
	$(LD) -T linker.ld start.o uart.o print.o -o kernel.elf

kernel.img: kernel.elf
	$(OBJCOPY) kernel.elf -O binary kernel.img

clean:
	rm -f *.o *.elf *.img
