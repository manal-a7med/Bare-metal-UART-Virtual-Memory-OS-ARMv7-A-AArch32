// uart.h
#ifndef UART_H
#define UART_H

void uart_init();
void uart_send(char c);
char uart_recv();
void uart_puts(const char *s);

#endif
