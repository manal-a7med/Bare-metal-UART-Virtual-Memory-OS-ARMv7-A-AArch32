CROSS_COMPILE = arm-none-eabi-
CC = $(CROSS_COMPILE)gcc
AS = $(CROSS_COMPILE)as
LD = $(CROSS_COMPILE)ld
OBJCOPY = $(CROSS_COMPILE)objcopy

CFLAGS = -Wall -O2 -nostdlib -ffreestanding -mcpu=cortex-a7 -marm -I.
LDFLAGS = -nostdlib

KERNEL_OBJS = kernel/entry.o kernel/kernel.o kernel/mmu.o kernel/uart.o
USER_OBJS = user/user_program.o

all: kernel8.img

kernel/%.o: kernel/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

kernel/%.o: kernel/%.S
	$(CC) $(CFLAGS) -c -o $@ $<

user/%.o: user/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

user_program.elf: $(USER_OBJS)
	$(LD) -T user/user.ld -o $@ $(USER_OBJS) $(LDFLAGS)

user_program.bin: user_program.elf
	$(OBJCOPY) -O binary $< $@

user_program.o: user_program.bin
	$(LD) -r -b binary -o $@ $<

kernel8.elf: $(KERNEL_OBJS) user_program.o
	$(LD) -T kernel/linker.ld -o $@ $(KERNEL_OBJS) user_program.o $(LDFLAGS)

kernel8.img: kernel8.elf
	$(OBJCOPY) -O binary $< $@

clean:
	rm -f kernel/*.o user/*.o *.elf *.img *.bin user_program.o

run: kernel8.img
	qemu-system-arm -M virt -cpu cortex-a7 -kernel kernel8.img -serial stdio -display none
