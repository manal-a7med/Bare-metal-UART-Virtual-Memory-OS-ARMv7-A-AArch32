ENTRY(_start)

SECTIONS
{
    /* Raspberry Pi 2 loads the kernel to 0x8000 */
    . = 0x8000;

    /* Text/code section */
    .text :
    {
        *(.text.entry)   /* Entry point (_start) */
        *(.text*)        /* Other code */
    }

    /* Read-only data section */
    .rodata :
    {
        *(.rodata*)
    }

    /* Initialized data section */
    .data :
    {
        *(.data*)
    }

    /* Uninitialized data section (cleared in startup) */
    .bss :
    {
        __bss_start = .;
        *(.bss*)
        *(COMMON)
        __bss_end = .;
    }

    /* Place the stack at the end of the image */
    . = ALIGN(8);
    .stack :
    {
        stack_bottom = .;
        . = . + 4096;     /* 4KB stack size */
        stack_top = .;
    }

    /DISCARD/ :
    {
        *(.note*)
        *(.comment*)
    }
}
