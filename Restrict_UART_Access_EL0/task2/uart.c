#include "uart.h"

#define DELAY() do { for(volatile int i=0; i<1000; i++); } while(0)

void uart_init(void) {

    register uint32_t reg_temp = 0;

    /* Disable UART */
    UART0_CR = 0;
    DELAY();

    /* Set baud rate to 115200 */
    UART0_IBRD = 1;
    UART0_IBRD = reg_temp;
    UART0_FBRD = 40;
    UART0_FBRD = reg_temp;
    DELAY();

    /* Configure line control */
    reg_temp = (1<<4) | (3<<5); /* 8N1, FIFO enable */
    UART0_LCRH = reg_temp;
    DELAY();

    /* Enable UART */
    reg_temp = (1<<0) | (1<<8) | (1<<9); /* UARTEN, TXE, RXE */
    UART0_CR = reg_temp;
    DELAY();}

void uart_putc(char c) {
    while (UART0_FR & FR_TXFF);
    UART0_DR = c;
    DELAY();
}

void uart_puts(const char *s) {
    while (*s) {
        if (*s == '\n') uart_putc('\r');
        uart_putc(*s++);
    }
}

char uart_getc(void) {
    while (UART0_FR & FR_RXFE);
    return UART0_DR;
}
