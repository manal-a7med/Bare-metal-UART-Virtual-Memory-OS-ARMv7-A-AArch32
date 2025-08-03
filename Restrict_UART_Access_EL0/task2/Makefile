CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
AS = arm-none-eabi-as
OBJCOPY = arm-none-eabi-objcopy

CFLAGS = -Wall -O2 -ffreestanding -nostdlib -nostartfiles \
         -mcpu=cortex-a7 \
         -fno-builtin -fno-strict-aliasing
ASFLAGS = -mcpu=cortex-a7
LDFLAGS = -T linker.ld -nostdlib --gc-sections

TARGET = kernel
OBJECTS = start.o uart.o user.o

.PHONY: all clean run

all: $(TARGET).img

$(TARGET).img: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

$(TARGET).elf: $(OBJECTS)
	$(LD) $(LDFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	$(CC) $(ASFLAGS) -c $< -o $@

clean:
	rm -f *.o *.elf *.img

run: $(TARGET).img
	qemu-system-arm -M raspi2b -kernel $(TARGET).img -nographic -serial null
