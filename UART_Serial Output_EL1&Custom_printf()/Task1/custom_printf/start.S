.section .text.entry
.arch armv7-a
.arm
.global _start
_start:
    // Initialize stack pointer with proper alignment
    ldr sp, =_stack_top
    mov r0, #0
    mov r1, #0
    mov r2, #0
    mov r3, #0
    mov r4, #0
    mov r5, #0
    mov r6, #0
    mov r7, #0
    mov r8, #0
    mov r9, #0
    mov r10, #0
    mov r11, #0
    mov r12, #0

    // Clear .bss
    ldr r0, =__bss_start
    ldr r1, =__bss_end
    mov r2, #0
bss_clear:
    cmp r0, r1
    strlt r2, [r0], #4
    blt bss_clear

    bl uart_init

    ldr r0, =msg
    bl uart_puts

    ldr r0, =main_msg
    bl uart_puts

    bl main

    // Should never reach here if main has while(1)
    ldr r0, =after_main
    bl uart_puts

hang:
    b hang

.section .bss
    .align 4
    .space 0x4000     // Increased stack size to 16KB
_stack_top:

.section .rodata
msg:
    .asciz ">>> UART works in start.S\n"
main_msg:
    .asciz ">>> Calling main()\n"
after_main:
    .asciz ">>> Back from main()\n"
