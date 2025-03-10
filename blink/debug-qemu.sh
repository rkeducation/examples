#!/bin/bash

# Variables
BINARY="build/program.bin"
ELF="build/program.elf"
QEMU="qemu-system-arm"
MACHINE="virt"  # Generic ARMv7-M machine with Cortex-M33 support
CPU="cortex-m33"
PORT="1234"     # GDB server port

# Check if binary exists, build if not
build() {
    if [ ! -f "$BINARY" ]; then
        echo "Building project..."
        make
        if [ $? -ne 0 ]; then
            echo "Build failed!"
            exit 1
        fi
    fi
}

# Run QEMU in the background
run_qemu() {
    echo "Starting QEMU for Cortex-M33 emulation..."
    $QEMU -cpu $CPU \
          -machine $MACHINE \
          -nographic \
          -semihosting \
          -kernel $BINARY \
          -gdb tcp::$PORT \
          -S &  # -S: Wait for GDB connection
    QEMU_PID=$!
    sleep 2  # Give QEMU time to start
}

# Connect GDB for debugging
debug_gdb() {
    echo "Starting GDB for debugging..."
    arm-none-eabi-gdb $ELF \
        -q \
        -x <(echo -e "target remote localhost:$PORT\nload\nbreak main\ncontinue")
}

# Cleanup on exit
cleanup() {
    echo "Stopping QEMU..."
    kill $QEMU_PID 2>/dev/null
}

# Trap Ctrl+C to cleanup
trap cleanup EXIT

# Main execution
build
run_qemu
debug_gdb

echo "Debug session ended."