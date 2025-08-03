ENTRY(_start)

MEMORY {
    RAM : ORIGIN = 0x8000, LENGTH = 128M
}

SECTIONS {
    . = 0x8000;

    .text : {
        *(.text.entry)
        *(.text)
        *(.text.*)
        KEEP(*(.text.uart_*))
    } > RAM

    .rodata : {
        *(.rodata)
        *(.rodata*)
    } > RAM

    .data : {
        *(.data)
        *(.data*)
    } > RAM

    .bss : {
        __bss_start = .;
        *(.bss)
        *(.bss*)
        *(COMMON)
        __bss_end = .;
    } > RAM

    . = ALIGN(8);
    _stack_top = . + 0x4000; /* 16KB stack */
}
