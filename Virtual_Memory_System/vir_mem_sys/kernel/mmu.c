#include "mmu.h"
#include "uart.h"

static uint32_t translation_table[4096] __attribute__((aligned(16384)));

void map_page(uint32_t *ttbr0, uint32_t virt, uint32_t phys, uint32_t flags) {
    uint32_t idx = virt >> 20;
    ttbr0[idx] = (phys & 0xFFF00000) | flags | 0x2; // Section entry
}

void mmu_init(void) {
    // Identity map first 1MB for kernel startup
    for (uint32_t i = 0; i < 256; i++) {
        map_page(translation_table, i << 20, i << 20, 
                AP_RW_K | MEM_NORMAL_WB);
    }
    
    // Map UART (0x3F201000) to same physical address
    map_page(translation_table, 0x3F200000, 0x3F200000, 
            AP_RW_K | MEM_DEVICE);
    
    // Map user space
    map_page(translation_table, USER_START, USER_START, 
            AP_RW_D | MEM_NORMAL_WB);
    
    // Set TTBR0
    asm volatile("mcr p15, 0, %0, c2, c0, 0" :: "r"(translation_table));
    
    // Set DACR to client mode for all domains
    asm volatile("mcr p15, 0, %0, c3, c0, 0" :: "r"(0x55555555));
}

void load_user_program(void *dest, void *src, uint32_t size) {
    // Simple memcpy for now
    char *d = dest;
    char *s = src;
    for (uint32_t i = 0; i < size; i++) {
        d[i] = s[i];
    }
}
