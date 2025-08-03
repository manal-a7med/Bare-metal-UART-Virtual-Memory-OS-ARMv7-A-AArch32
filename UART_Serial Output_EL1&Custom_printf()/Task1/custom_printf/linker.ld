ENTRY(_start)

MEMORY {
    RAM : ORIGIN = 0x8000, LENGTH = 128M
}

SECTIONS {
    . = 0x8000;

    .text : {
        *(.text.entry)
        *(.text*)
    } > RAM

    .rodata : {
        *(.rodata*)
    } > RAM

    .data : {
        *(.data*)
    } > RAM

    .bss : {
        __bss_start = .;
        *(.bss*)
        __bss_end = .;
    } > RAM

    /DISCARD/ : {
        *(.comment)
        *(.note*)
    }
}
