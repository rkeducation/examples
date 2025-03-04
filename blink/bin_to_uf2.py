#!/usr/bin/env python3

import sys
import os
import struct

# UF2 constants for RP2350
UF2_MAGIC_START0 = 0x0A324655  # "UF2\n"
UF2_MAGIC_START1 = 0x9E5D5157
UF2_MAGIC_END = 0x0AB16F30
RP2350_FAMILY_ID = 0xE48BFF56
BLOCK_SIZE = 256               # Payload size per block
FLASH_ADDR = 0x10000000        # RP2350 flash start address

def create_uf2_block(data, addr, block_num, total_blocks):
    """Create a single 512-byte UF2 block."""
    # Header is 32 bytes
    header = struct.pack(
        '<IIIIIIII',           # Little-endian, 8 x 32-bit unsigned ints
        UF2_MAGIC_START0,      # Magic start 0
        UF2_MAGIC_START1,      # Magic start 1
        0x00000000,            # Flags (none)
        addr,                  # Target address
        BLOCK_SIZE,            # Payload size (256 bytes)
        block_num,             # Block number
        total_blocks,          # Total blocks
        RP2350_FAMILY_ID       # Family ID
    )
    print(f"Header size: {len(header)} bytes")  # Debug

    # Payload is 256 bytes (pad with zeros if needed)
    payload = data.ljust(BLOCK_SIZE, b'\x00')
    print(f"Payload size: {len(payload)} bytes")  # Debug

    # Padding is (476 - BLOCK_SIZE) bytes to make data section 476 bytes
    padding_size = 476 - BLOCK_SIZE  # For BLOCK_SIZE=256, padding=220 bytes
    padding = b'\x00' * padding_size
    print(f"Padding size: {padding_size} bytes")  # Debug

    # Footer is 4 bytes
    footer = struct.pack('<I', UF2_MAGIC_END)
    print(f"Footer size: {len(footer)} bytes")  # Debug

    # Combine all parts: header + payload + padding + footer
    block = header + payload + padding + footer
    print(f"Total block size: {len(block)} bytes")  # Debug
    assert len(block) == 512, f"Block size is {len(block)}, expected 512"
    return block

def convert_bin_to_uf2(input_file, output_file):
    """Convert a binary file to UF2 format."""
    # Read the binary file
    with open(input_file, 'rb') as f:
        bin_data = f.read()
    
    bin_size = len(bin_data)
    total_blocks = (bin_size + BLOCK_SIZE - 1) // BLOCK_SIZE  # Ceiling division
    
    print(f"Generating {output_file} from {input_file} ({bin_size} bytes, {total_blocks} blocks)...")
    
    # Write UF2 file
    with open(output_file, 'wb') as f:
        offset = 0
        block_num = 0
        while offset < bin_size:
            # Extract up to BLOCK_SIZE bytes
            chunk = bin_data[offset:offset + BLOCK_SIZE]
            addr = FLASH_ADDR + offset
            block = create_uf2_block(chunk, addr, block_num, total_blocks)
            f.write(block)
            offset += BLOCK_SIZE
            block_num += 1
    
    print(f"Created {output_file}")

def main():
    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} <input_file.bin>")
        print("Output will be <input_file>.uf2")
        sys.exit(1)
    
    input_file = sys.argv[1]
    if not os.path.isfile(input_file):
        print(f"Error: {input_file} not found")
        sys.exit(1)
    
    base_name = os.path.splitext(input_file)[0]
    output_file = f"{base_name}.uf2"
    
    convert_bin_to_uf2(input_file, output_file)

if __name__ == "__main__":
    main()