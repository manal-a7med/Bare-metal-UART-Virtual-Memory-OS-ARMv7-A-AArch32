ENTRY(_start)

SECTIONS {
    . = 0x100000;
    
    .text : {
        *(.text*)
    }
    
    .rodata : {
        *(.rodata*)
    }
    
    .data : {
        *(.data*)
    }
    
    .bss : {
        *(.bss*)
    }
    
    . = ALIGN(8);
    _stack_top = . + 0x10000;
}
