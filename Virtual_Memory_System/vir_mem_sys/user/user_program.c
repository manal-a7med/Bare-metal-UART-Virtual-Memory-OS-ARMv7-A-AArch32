void _start(void) {
    // This will cause an exception since UART is kernel-only
    // We'll handle this with system calls in a real OS
    volatile char *uart = (char*)0x3F201000;
    
    // Print message (would normally use syscall)
    char *msg = "Hello from user space!\n";
    while (*msg) {
        *uart = *msg++;
    }
    
    // Loop forever
    while(1);
}
