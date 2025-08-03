.section .text.entry
.arch armv7-a
.arm
.global _start

_start:
    /* Initialize all general-purpose registers to zero */
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

    /* Check current mode */
    mrs r0, cpsr
    and r0, r0, #0x1F
    cmp r0, #0x13           /* Supervisor mode */
    bne .                   /* Halt if not */

    /* Setup stack */
    ldr sp, =_stack_top

    /* Clear BSS */
    ldr r0, =__bss_start
    ldr r1, =__bss_end
    mov r2, #0
clear_bss:
    cmp r0, r1
    strlt r2, [r0], #4
    blt clear_bss

    /* Initialize hardware */
    bl uart_init

    /* Print boot message */
    ldr r0, =boot_msg
    bl uart_puts

    /* Switch to User mode */
    mov r0, #0x10           /* User mode */
    msr spsr_cxsf, r0
    ldr lr, =user_entry
    movs pc, lr             /* Switch mode */

user_entry:
    /* User mode code */
    ldr r0, =user_msg
    bl uart_puts            /* Will fault */

    /* Proper syscall */
    ldr r0, =syscall_msg
    mov r7, #0              /* SYS_WRITE */
    svc #0

    /* Hang */
    b .

/* SWI Handler */
.global vector_swi
vector_swi:
    cmp r7, #0              /* SYS_WRITE */
    bne 1f
    push {r0-r1, lr}
    bl uart_puts
    pop {r0-r1, lr}
1:  movs pc, lr

.section .rodata
boot_msg:     .asciz "System booted in Supervisor mode\n"
user_msg:     .asciz "Attempting direct UART access (should fault)\n"
syscall_msg:  .asciz "Proper output via syscall\n"

.section .bss
.align 4
_stack_top: .space 0x4000
