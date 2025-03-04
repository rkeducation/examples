Based on the RP2350 datasheet, here are some key updates:

1. Memory and Peripheral Base Addresses for RP2350
SIO Base: 0xD0000000
GPIO Base: 0x40028000
Clocks Base: 0x40010000
Resets Base: 0x40020000
2. Updated GPIO and Reset Register Offsets
GPIO Enable Register: GPIO_BASE + 0x04
GPIO Output Enable Register (OE): SIO_BASE + 0x020
GPIO Output Register (OUT): SIO_BASE + 0x010
Resets Register: RESETS_BASE + 0x00
Resets Done Register: RESETS_BASE + 0x08
3. Clock Configuration Updates
Clock Reference Base: CLOCKS_BASE = 0x40010000
E

## Convert blink.bin to UF2 (if using the bootloader):
python uf2conv.py -f 0xE48BFF56 -c blink.bin -o blink.uf2

## Copy file to rp2350
cp blink.uf2 /Volumes/RPI-RP2/  # macOS