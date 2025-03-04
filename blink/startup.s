.section .vectors, "ax"
.cpu cortex-m33         // Specify Cortex-M33 (ARMv8-M Mainline)
.thumb                  // Use Thumb instruction set
.align 2
.global _vectors

_vectors:
    .word 0x10008000    // Initial stack pointer (SRAM end: 520KB SRAM at 0x10000000)
    .word _reset_handler  // Reset handler
    .word 0             // NMI handler (not used)
    .word 0             // HardFault handler (not used)
    // Add more vectors here if needed (e.g., interrupts), up to 48 for Cortex-M33

.section .text
.align 2
.global _reset_handler
.type _reset_handler, %function

_reset_handler:
    // Clear BSS section (zero-initialized data)
    ldr r0, =__bss_start__
    ldr r1, =__bss_end__
    mov r2, #0
bss_clear_loop:
    cmp r0, r1
    bge bss_clear_done
    str r2, [r0]        // Store 0 at address in r0
    add r0, r0, #4      // Increment r0 by 4 (next word)
    b bss_clear_loop
bss_clear_done:

    // Jump to main
    bl main

    // Infinite loop in case main returns
hang:
    b hang

.size _reset_handler, . - _reset_handler
