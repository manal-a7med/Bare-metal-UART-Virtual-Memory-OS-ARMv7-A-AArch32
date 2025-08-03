#include "uart.h"
#include <stdint.h>

#define UART0_BASE 0x3F201000

volatile unsigned int * const UART0_DR = (unsigned int *)UART0_BASE;
volatile unsigned int * const UART0_FR = (unsigned int *)(UART0_BASE + 0x18);

void uart_init(void) {
    // Assume UART is already initialized by bootloader
}

void uart_putc(char c) {
    while (*UART0_FR & (1 << 5));
    *UART0_DR = c;
}

void uart_puts(const char *s) {
    while (*s) {
        if (*s == '\n')
            uart_putc('\r');
        uart_putc(*s++);
    }
}

void uart_hex(uint32_t val) {
    for (int i = 28; i >= 0; i -= 4) {
        char c = (val >> i) & 0xF;
        uart_putc(c < 10 ? '0' + c : 'A' + c - 10);
    }
}
