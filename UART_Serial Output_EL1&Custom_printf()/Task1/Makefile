# Toolchain setup
CROSS_COMPILE = arm-none-eabi-
CC      = $(CROSS_COMPILE)gcc
AS      = $(CROSS_COMPILE)as
LD      = $(CROSS_COMPILE)ld
OBJCOPY = $(CROSS_COMPILE)objcopy
RM      = rm -f

# Files
TARGET = kernel
SRC    = uart.c start.S
OBJ    = uart.o start.o
LD_SCRIPT = linker.ld

# Flags
CFLAGS  = -Wall -O2 -nostdlib -nostartfiles -ffreestanding
LDFLAGS = -T $(LD_SCRIPT)

# Default target
all: $(TARGET).img

# Compile .c files to .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Assemble .S files to .o files
%.o: %.S
	$(AS) $< -o $@

# Link .o files to create the final ELF binary
$(TARGET).elf: $(OBJ)
	$(LD) $(LDFLAGS) $^ -o $@

# Convert ELF binary to raw binary format for the Raspberry Pi
$(TARGET).img: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

# Clean the project (only remove generated files)
clean:
	$(RM) *.o *.elf *.img
