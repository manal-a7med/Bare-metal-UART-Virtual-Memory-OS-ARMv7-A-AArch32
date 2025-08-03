# ARMv7 Virtual Memory OS with MMU Support

## Key Features

1. **Virtual Memory System**:
   - ARMv7 MMU configuration with two-level page tables
   - 4KB page granularity
   - Separate kernel (0x8000+) and user (0x100000+) address spaces

2. **Memory Protection**:
   - Kernel space: RWX in supervisor mode only
   - User space: RW in user mode, none in kernel
   - MMIO regions (UART): Kernel-only device memory mapping

3. **System Call Interface**:
   - SVC-based syscall mechanism
   - Secure UART output from user space
   - Register-based argument passing (r0-r3)

4. **Exception Handling**:
   - Basic exception vectors for all ARM modes
   - Data/prefetch abort handlers with debug output
   - Undefined instruction handler

## Implementation Highlights

### Memory Management
- Translation tables at 0x80000 (16KB aligned)
- Kernel identity mapping (1:1 physical/virtual)
- User space mapped with restricted permissions
- MMIO regions mapped as device memory

### System Calls
1. User triggers `svc #0` with:
   - r0: syscall number
   - r1: string pointer (for write syscall)
2. Kernel validates pointers
3. Performs operation (e.g., UART output)
4. Returns to user mode

### Security Model
- User programs cannot:
  - Access kernel memory
  - Directly access hardware
  - Modify page tables
- All privileged operations require syscalls

## Building & Running

```bash
# Clone and setup
git clone https://github.com/yourrepo/armv7-mmu-os.git
cd armv7-mmu-os

# Build
make clean
make

# Run in QEMU
make run

[MMU] Initialized translation tables
[KERNEL] Mapped UART at 0x3F200000
[USER] Hello World from user mode!
[SYSCALL] Clean exit


+---------------------+ 0xFFFFFFFF
|       Reserved      |
+---------------------+ 0xC0000000
|   Kernel Devices    |
| (MMIO, UART, etc.)  |
+---------------------+ 0x80000000
|   Kernel Space      |
| (Code, Data, Heap)  |
+---------------------+ 0x00010000
|    User Programs    |
+---------------------+ 0x00008000
|  Kernel Bootloader  |
+---------------------+ 0x00000000

page table structure

+---------------------+
|  L1 Page Table      |
| (4096 x 32-bit      |
|  entries)           |
+----------+----------+
           |
           v
+---------------------+
|  L2 Page Tables     |
| (256 x 1KB pages    |
|  per L1 entry)      |
+---------------------+


system call flow ascii
+---------------------+
|   User Mode         |
| 1. Prepares args    |
| 2. Executes SVC #0  |
+---------+-----------+
          |
          v
+---------------------+
|   Exception Handler |
| 1. Saves context    |
| 2. Validates args   |
| 3. Calls syshandler |
+---------+-----------+
          |
          v
+---------------------+
|   Kernel Service    |
| (UART output, etc.) |
+---------+-----------+
          |
          v
+---------------------+
|   Return to User    |
| 1. Restores context |
| 2. ERET instruction |
+---------------------+

exception handling
+---------------------+
|   Vector Table      |
+---------+-----------+
          |
          v
+---------------------+
|   Exception Handler |
| 1. Identify cause   |
| 2. Print debug info |
| 3. Kill process or  |
|    recover if possible
+---------------------+

build process

+---------------------+
|   Source Files      |
| (entry.S, mmu.c,    |
|  hello.c, etc.)     |
+---------+-----------+
          |
          v
+---------------------+
|   Compilation       |
| (arm-none-eabi-gcc) |
+---------+-----------+
          |
          v
+---------------------+
|   Linking           |
| (Separate kernel    |
|  and user images)   |
+---------+-----------+
          |
          v
+---------------------+
|   Final OS Image    |
| (kernel8.img)       |
+---------------------+
