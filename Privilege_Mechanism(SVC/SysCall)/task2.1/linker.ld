ENTRY(_start)

MEMORY {
    RAM : ORIGIN = 0x8000, LENGTH = 128M
}

SECTIONS {
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
    
    . = ALIGN(8);
    _stack_top = . + 0x1000;
    user_stack_top = . + 0x2000;
}
