// main.c
#include "uart.h"
#include <stdarg.h>

void itoa(int value, char *buf) {
    char tmp[16];
    int i = 0, j = 0, neg = 0;

    if (value == 0) {
        buf[0] = '0'; buf[1] = '\0'; return;
    }

    if (value < 0) {
        neg = 1;
        value = -value;
    }

    while (value) {
        tmp[i++] = '0' + (value % 10);
        value /= 10;
    }

    if (neg) tmp[i++] = '-';

    while (i--) buf[j++] = tmp[i];
    buf[j] = '\0';
}

void utoa(unsigned int value, char *buf) {
    char tmp[16];
    int i = 0, j = 0;

    if (value == 0) {
        buf[0] = '0'; buf[1] = '\0'; return;
    }

    while (value) {
        tmp[i++] = '0' + (value % 10);
        value /= 10;
    }

    while (i--) buf[j++] = tmp[i];
    buf[j] = '\0';
}

void vprintf(const char *fmt, va_list args) {
    char buf[128];
    for (; *fmt; fmt++) {
        if (*fmt == '%') {
            fmt++;
            switch (*fmt) {
                case 'c': uart_send((char)va_arg(args, int)); break;
                case 's': uart_puts(va_arg(args, char *)); break;
                case 'd': itoa(va_arg(args, int), buf); uart_puts(buf); break;
                case 'u': utoa(va_arg(args, unsigned int), buf); uart_puts(buf); break;
                default: uart_send('%'); uart_send(*fmt); break;
            }
        } else {
            uart_send(*fmt);
        }
    }
}

void printf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
}

void main() {
    uart_init();
//    uart_send('X');
    uart_puts(">>> Entered main\n");
    uart_puts("UART Initialized!\n");
    printf("Hello World!\n");

    int x = 123;
    unsigned int y = 456;
    char c = 'A';
    char *s = "string";

    printf("x = %d, y = %u, c = %c, s = %s\n", x, y, c, s);
    while (1);  // prevent returning
}
