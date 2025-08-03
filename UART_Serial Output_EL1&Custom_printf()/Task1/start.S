.section .text.entry
.syntax unified
.arch armv7-a
.arm
.global _start

// Define memory addresses and constants
#define MMIO_BASE      0x3F000000
#define UART0_BASE     (MMIO_BASE + 0x201000)
#define UART0_DR       (UART0_BASE + 0x00)

// Entry point for the program
_start:
    // Initialize the stack pointer (sp) to the top of the stack
    ldr sp, =_stack_top

    // Optional: zero .bss section (currently unused but good practice)
    ldr r0, =__bss_start
    ldr r1, =__bss_end
bss_clear:
    cmp r0, r1
    it lt
    movlt r2, #0   // Executes if the condition for LT (Less Than) is met
    strlt r2, [r0], #4
    moveq r2, #0
    strlt r2, [r0], #4

    blt bss_clear

    // Call the uart_init function (located in uart.c)
    bl uart_init

    // Call the main function (also in uart.c)
    bl main

    // Infinite loop to hang the program (in case main returns)
hang:
    b hang

// Define a simple delay function (optional if needed elsewhere)
delay:
    mov r1, r0
delay_loop:
    subs r1, r1, #1
    bne delay_loop
    bx lr

// Reserve space for the stack
.section .bss
    .space 0x1000  // 4KB stack
_stack_top:
