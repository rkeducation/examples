MEMORY {
    FLASH (rx) : ORIGIN = 0x10000000, LENGTH = 4M  /* Flash memory */
    SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 520K /* SRAM */
}

SECTIONS {
    .vectors : {
        KEEP(*(.vectors))
    } > FLASH

    .text : {
        *(.text*)
        *(.rodata*)
    } > FLASH

    .data : {
        __data_start__ = .;
        *(.data*)
        __data_end__ = .;
    } > SRAM AT > FLASH

    .bss : {
        __bss_start__ = .;
        *(.bss*)
        *(COMMON)
        __bss_end__ = .;
    } > SRAM

    /* Stack at the end of SRAM */
    __stack_start__ = ORIGIN(SRAM) + LENGTH(SRAM);
}