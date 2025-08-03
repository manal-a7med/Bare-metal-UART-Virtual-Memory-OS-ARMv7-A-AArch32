.section .text.entry
.syntax unified
.arch armv7-a
.arm

.global _start
.extern main
.extern uart_init
.extern uart_puts
.extern handle_svc

_start:
    ldr sp, =_stack_top
    
    // Clear .bss
    ldr r0, =__bss_start
    ldr r1, =__bss_end
    mov r2, #0
bss_clear:
    cmp r0, r1
    strlt r2, [r0], #4
    blt bss_clear

    bl uart_init
    ldr r0, =bootmsg
    bl uart_puts

    // Switch to User mode
    ldr sp, =user_stack_top
    msr cpsr_c, #0x10  // User mode
    
    // Clear registers
    eor r0, r0, r0
    eor r1, r1, r1
    eor r2, r2, r2
    eor r3, r3, r3
    
    bl main

    // Should never reach here
hang: b hang

svc_handler:
    push {r0-r3, lr}
    mov r0, #0  // Default service number
    bl handle_svc
    pop {r0-r3, lr}
    movs pc, lr  // Return from exception

.section .rodata
bootmsg: .asciz ">>> Booting in EL1, switching to EL0...\n"

.section .bss
.align 4
_stack_top: .space 0x1000

.section .bss.user
.align 4
user_stack_top: .space 0x1000
