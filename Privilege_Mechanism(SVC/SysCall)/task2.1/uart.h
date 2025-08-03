#ifndef UART_H
#define UART_H

#define MMIO_BASE       0x3F000000
#define UART0_BASE      (MMIO_BASE + 0x201000)

void uart_init(void);
void uart_send(char c);
void uart_puts(const char *s);
void svc_call(int num, const char *msg);

#endif
