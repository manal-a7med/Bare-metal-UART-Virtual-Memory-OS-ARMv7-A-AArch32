#ifndef SYSCALL_H
#define SYSCALL_H

#include <stdint.h>
#include <stddef.h>

#define SYS_WRITE 0
#define SYS_EXIT  1

static inline uint32_t syscall(uint32_t num, const char* str) {
    register uint32_t r0 asm("r0") = (uint32_t)str;
    register uint32_t r7 asm("r7") = num;

    __asm__ __volatile__(
        "svc #0\n"
        : "+r"(r0)
        : "r"(r7)
        : "memory"
    );
    return r0;
}

static inline void user_puts(const char* s) {
    syscall(SYS_WRITE, s);
}

static inline void user_exit(void) {
    syscall(SYS_EXIT, NULL);
}

#endif
