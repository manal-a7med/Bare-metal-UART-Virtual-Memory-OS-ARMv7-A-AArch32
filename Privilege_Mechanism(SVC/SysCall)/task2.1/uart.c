#include <stdint.h>
#include "uart.h"

// UART Register Definitions
#define UART0_DR        (*((volatile uint32_t*)(UART0_BASE + 0x00)))
#define UART0_FR        (*((volatile uint32_t*)(UART0_BASE + 0x18)))
#define UART0_IBRD      (*((volatile uint32_t*)(UART0_BASE + 0x24)))
#define UART0_FBRD      (*((volatile uint32_t*)(UART0_BASE + 0x28)))
#define UART0_LCRH      (*((volatile uint32_t*)(UART0_BASE + 0x2C)))
#define UART0_CR        (*((volatile uint32_t*)(UART0_BASE + 0x30)))
#define UART0_IMSC      (*((volatile uint32_t*)(UART0_BASE + 0x38)))
#define UART0_ICR       (*((volatile uint32_t*)(UART0_BASE + 0x44)))

#define FR_TXFF         (1 << 5)
#define FR_RXFE         (1 << 4)

void uart_init() {
    // Disable UART
    UART0_CR = 0;
    
    // Clear pending interrupts
    UART0_ICR = 0x7FF;
    
    // Set baud rate (115200)
    UART0_IBRD = 26;
    UART0_FBRD = 3;
    
    // Enable FIFO, 8-bit data
    UART0_LCRH = (1 << 4) | (1 << 5) | (1 << 6);
    
    // Mask all interrupts
    UART0_IMSC = 0;
    
    // Enable UART, Tx, Rx
    UART0_CR = (1 << 0) | (1 << 8) | (1 << 9);
}

void uart_send(char c) {
    // Check current mode
    unsigned int mode;
    asm volatile("mrs %0, cpsr" : "=r"(mode));
    mode &= 0x1F;

    // User mode is 0x10
    if (mode == 0x10) {
        while(1); // Hang if direct UART access from EL0
    }

    while (UART0_FR & FR_TXFF);
    UART0_DR = c;
}

void uart_puts(const char *s) {
    while (*s) {
        if (*s == '\n') uart_send('\r');
        uart_send(*s++);
    }
}

void svc_call(int num, const char *msg) {
    register int r0 asm("r0") = num;
    register const char *r1 asm("r1") = msg;
    asm volatile("svc #0" : : "r"(r0), "r"(r1));
}
