// RP2350 register definitions (base addresses from RP2350 datasheet)
#define SIO_BASE        0xd0000000
#define GPIO_OUT_SET    (SIO_BASE + 0x14)  // Set bits in GPIO output
#define GPIO_OUT_CLR    (SIO_BASE + 0x18)  // Clear bits in GPIO output
#define GPIO_OE_SET     (SIO_BASE + 0x24)  // Set GPIO output enable

#define IO_BANK0_BASE   0x40014000
#define GPIO25_CTRL     (IO_BANK0_BASE + 0x0cc)  // GPIO25 control register

#define PADS_BANK0_BASE 0x4001c000
#define GPIO25_PAD      (PADS_BANK0_BASE + 0x68)  // GPIO25 pad control

// Simple delay function
void delay(unsigned int count) {
    while (count--) {
        __asm("nop");
    }
}

// Write to a register
static inline void reg_write(volatile unsigned int *addr, unsigned int value) {
    *addr = value;
}

int main(void) {
    // Configure GPIO25 pad: enable output, no pull-ups/pull-downs
    reg_write((volatile unsigned int *)GPIO25_PAD, 0x56);  // Default drive strength, output enabled

    // Set GPIO25 function to SIO (function 5)
    reg_write((volatile unsigned int *)GPIO25_CTRL, 5);

    // Enable output on GPIO25
    reg_write((volatile unsigned int *)GPIO_OE_SET, 1 << 25);

    // Blink loop
    while (1) {
        reg_write((volatile unsigned int *)GPIO_OUT_SET, 1 << 25);  // LED on
        delay(500000);  // Rough delay (~0.5s at 12 MHz)
        reg_write((volatile unsigned int *)GPIO_OUT_CLR, 1 << 25);  // LED off
        delay(500000);
    }

    return 0;  // Will never reach here
}