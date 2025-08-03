#include "uart.h"

void main() {
    // Test SVC call
    svc_call(0, "Hello from EL0 via SVC!\n");
    
    // This would hang if uncommented
    // uart_puts("Direct UART access from EL0\n");
    
    while(1) {
        // Stay in EL0
        asm volatile("nop");
    }
}
