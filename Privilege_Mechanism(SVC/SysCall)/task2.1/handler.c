#include "uart.h"

void handle_svc(int num, const char *msg) {
    switch(num) {
        case 0:
            uart_puts(msg);
            break;
        default:
            uart_puts("Unknown SVC call\n");
            break;
    }
}
