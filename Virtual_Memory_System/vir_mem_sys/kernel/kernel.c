#include "uart.h"
#include "mmu.h"
#include <stdint.h>

/* These are provided by the binary object */
extern uint8_t _binary_user_program_bin_start[];
extern uint8_t _binary_user_program_bin_end[];
#define USER_PROGRAM_START _binary_user_program_bin_start
#define USER_PROGRAM_END _binary_user_program_bin_end

void kernel_main(void) {
    uart_init();
    uart_puts("Kernel booted, setting up MMU...\n");
    
    // Load user program
    uint32_t user_size = (uint32_t)(USER_PROGRAM_END - USER_PROGRAM_START);
    
    load_user_program((void*)USER_START, USER_PROGRAM_START, user_size);
    
    uart_puts("User program loaded at 0x");
    uart_hex(USER_START);
    uart_puts(", size: ");
    uart_hex(user_size);
    uart_puts(" bytes\n");
    
    // Jump to user program
    uart_puts("Entering user mode...\n");
    asm volatile(
        "mov r0, #0x10\n"    // User mode
        "msr cpsr_c, r0\n"
        "mov sp, %0\n"
        "bx %1"
        :: "r"(USER_START + 0x10000), "r"(USER_START) : "r0");
    
    while(1);
}
