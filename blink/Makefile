# Toolchain settings
CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
LD = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy

# Compiler and assembler flags
CFLAGS = -mthumb -mcpu=cortex-m33 -O2 -Wall
ASFLAGS = -mcpu=cortex-m33 -mthumb
LDFLAGS = -nostdlib -T linker.ld


# Source files
SOURCES = main.c startup.s
OBJECTS = main.o startup.o
TARGET = blink.elf
BINARY = blink.bin
UF2 = blink.uf2

# Default target
all: $(BINARY)

# Compile C files
main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

# Assemble startup file
startup.o: startup.s
	$(AS) $(ASFLAGS) -o $@ $<

# Link objects
$(TARGET): $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $(OBJECTS)

# Generate binary
$(BINARY): $(TARGET)
	$(OBJCOPY) -O binary $< $@

# Clean up
clean:
	rm -f *.o *.elf *.bin *.uf2

# Flash to device (optional)
flash: $(UF2)
	@echo "Copy $(UF2) to the RP2350 in BOOTSEL mode"

.PHONY: all clean flash