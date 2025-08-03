#define MMIO_BASE       0x3F000000
#define GPFSEL1         ((volatile unsigned int*)(MMIO_BASE + 0x200004))
#define GPPUD           ((volatile unsigned int*)(MMIO_BASE + 0x200094))
#define GPPUDCLK0       ((volatile unsigned int*)(MMIO_BASE + 0x200098))
#define UART0_BASE      (MMIO_BASE + 0x201000)

#define UART0_DR        ((volatile unsigned int*)(UART0_BASE + 0x00))
#define UART0_FR        ((volatile unsigned int*)(UART0_BASE + 0x18))
#define UART0_IBRD      ((volatile unsigned int*)(UART0_BASE + 0x24))
#define UART0_FBRD      ((volatile unsigned int*)(UART0_BASE + 0x28))
#define UART0_LCRH      ((volatile unsigned int*)(UART0_BASE + 0x2C))
#define UART0_CR        ((volatile unsigned int*)(UART0_BASE + 0x30))
#define UART0_ICR       ((volatile unsigned int*)(UART0_BASE + 0x44))

static inline void delay(int count) {
    for (volatile int i = 0; i < count; i++) {}
}

void uart_init() {
    *UART0_CR = 0x00000000;

    *GPFSEL1 &= ~((7 << 12) | (7 << 15));
    *GPFSEL1 |= (4 << 12) | (4 << 15);

    *GPPUD = 0x00000000;
    delay(150);
    *GPPUDCLK0 = (1 << 14) | (1 << 15);
    delay(150);
    *GPPUDCLK0 = 0x00000000;

    *UART0_ICR = 0x7FF;
    *UART0_IBRD = 1;
    *UART0_FBRD = 40;
//    *UART0_LCRH = (1 << 4) | (3 << 5);
    *UART0_CR = (1 << 0) | (1 << 8) | (1 << 9);
}

void uart_send(char c) {
    while (*UART0_FR & (1 << 5)) {}
    *UART0_DR = c;
}

char uart_recv() {
    while (*UART0_FR & (1 << 4)) {}
    return (char)(*UART0_DR);
}

void uart_puts(const char* str) {
    while (*str) {
        if (*str == '\n') uart_send('\r');
        uart_send(*str++);
    }
}

//void main() {
//    uart_puts("UART Initialized!\n");
//    uart_puts("Hello World");

    // Echo loop: type in serial terminal, Pi echoes back
    //while (1) {
    //    char c = uart_recv();
    //    uart_send(c);
    //}
//}
