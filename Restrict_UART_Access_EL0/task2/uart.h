#ifndef UART_H
#define UART_H

#include <stdint.h>

#define UART0_BASE 0x3F201000

/* Register definitions */
#define UART_REG(offset) (*(volatile uint32_t*)(UART0_BASE + (offset)))
#define UART0_DR   UART_REG(0x00)
#define UART0_FR   UART_REG(0x18)
#define UART0_IBRD UART_REG(0x24)
#define UART0_FBRD UART_REG(0x28)
#define UART0_LCRH UART_REG(0x2C)
#define UART0_CR   UART_REG(0x30)

/* Status flags */
#define FR_TXFF    (1 << 5)
#define FR_RXFE    (1 << 4)

/* Function prototypes */
void uart_init(void);
void uart_putc(char c) __attribute__((target("arm")));
void uart_puts(const char *s) __attribute__((used, target("arm")));
char uart_getc(void);

#endif
