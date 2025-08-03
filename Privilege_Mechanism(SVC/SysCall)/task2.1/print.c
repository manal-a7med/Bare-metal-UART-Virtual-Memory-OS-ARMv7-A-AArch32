#include "uart.h"
#include <stdarg.h>

void itoa(int val, char *buf) {
    char tmp[16];
    int i = 0, j = 0, neg = 0;

    if (val == 0) {
        buf[0] = '0'; buf[1] = '\0'; return;
    }

    if (val < 0) {
        neg = 1;
        val = -val;
    }

    while (val) {
        tmp[i++] = '0' + (val % 10);
        val /= 10;
    }
    if (neg) tmp[i++] = '-';

    while (i--) buf[j++] = tmp[i];
    buf[j] = '\0';
}

void vprintf(const char *fmt, va_list args) {
    char buf[128];
    for (; *fmt; fmt++) {
        if (*fmt == '%') {
            fmt++;
            switch (*fmt) {
                case 'd': {
                    itoa(va_arg(args, int), buf);
                    svc_call(0, buf);
                    break;
                }
                case 'c': {
                    char c = (char)va_arg(args, int);
                    buf[0] = c; buf[1] = '\0';
                    svc_call(0, buf);
                    break;
                }
                case 's': {
                    svc_call(0, va_arg(args, char *));
                    break;
                }
                default: break;
            }
        } else {
            char c[2] = {*fmt, '\0'};
            svc_call(0, c);
        }
    }
}

void printf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
}
