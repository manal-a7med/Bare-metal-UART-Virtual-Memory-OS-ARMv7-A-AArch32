
# Bare-metal UART & Virtual Memory OS (ARMv7-A AArch32)

This project implements a bare-metal operating system targeting the Raspberry Pi 2B (ARM Cortex-A7, ARMv7-A architecture, AArch32 execution state). Developed without any underlying OS or standard runtime, it showcases direct hardware interaction through a custom UART driver, exception-level management, and a fully functioning virtual memory system.

## Features

- Low-level UART0 serial output with custom `printf` functionality (bare-metal, no standard library)
- Privilege separation with mode switching from EL1 (kernel) to EL0 (user)
- Supervisor Call (SVC) support enabling system calls from user space
- ARMv7-A MMU integration for section-mapped virtual memory
- Custom page table setup with translation table base registers (TTBR) and domain access control
- Virtualized user-mode program execution in protected memory space
- Emulated on QEMU using Raspberry Pi 2 model (`-M raspi2`)

- ## Build & Run

(bash)
make            # Builds the kernel image
make run        # Runs the image on QEMU using Raspberry Pi 2 emulation

## Project Repository

[GitHub: Bare-metal UART & Virtual Memory OS (ARMv7-A AArch32)](https://github.com/manal-a7med/Bare-metal-UART-Virtual-Memory-OS-ARMv7-A-AArch32)

## Author

Manal Ahmed Matheen
