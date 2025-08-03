.section ".text.boot"
.globl _start

_start:
    // Set stack pointer
    ldr sp, =_stack_top
    
    // Clear bss
    ldr r4, =__bss_start
    ldr r9, =__bss_end
    mov r5, #0
    mov r6, #0
    mov r7, #0
    mov r8, #0
    b       2f
1:  stmia   r4!, {r5-r8}
2:  cmp     r4, r9
    blo     1b

    // Setup MMU
    bl mmu_init
    
    // Enable MMU
    mrc p15, 0, r0, c1, c0, 0
    orr r0, r0, #1
    mcr p15, 0, r0, c1, c0, 0
    
    // Jump to kernel main
    bl kernel_main
    
    // Halt if we return
1:  b 1b

.globl _stack_top
_stack_top: .word 0x80000
