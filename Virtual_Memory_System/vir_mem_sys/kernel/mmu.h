#ifndef MMU_H
#define MMU_H

#include <stdint.h>

#define PAGE_SIZE 4096
#define KERNEL_START 0x8000
#define USER_START   0x100000

// Memory attributes
#define MEM_NORMAL_WB (0x3 << 2)
#define MEM_DEVICE    (0x0 << 2)

// Access permissions
#define AP_RW_D (0x3 << 10) // Read/write at all privilege levels
#define AP_RW_K (0x1 << 10) // Read/write in kernel only

void mmu_init(void);
void map_page(uint32_t *ttbr0, uint32_t virt, uint32_t phys, uint32_t flags);
void load_user_program(void *dest, void *src, uint32_t size);

#endif
