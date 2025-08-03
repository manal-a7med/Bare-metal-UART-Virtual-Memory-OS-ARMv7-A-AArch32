#include "syscall.h"

void user_main(void) {
    /* This would fault if uncommented */
    /* uart_puts("Direct access attempt\n"); */

    /* Proper output method */
    user_puts("Hello from User mode!\n");
    user_puts("Counting...\n");

    for (int i = 0; i < 3; i++) {
        char msg[] = { '0'+i, '\n', '\0' };
        user_puts(msg);
    }

    while (1); /* Never return */
}
