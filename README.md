
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



# Bare-metal UART & Virtual Memory OS (ARMv7-A AArch32)

This project is a low-level operating system developed for the Raspberry Pi 2B, based on the ARMv7-A architecture and AArch32 execution state. Built entirely from scratch without any reliance on an underlying operating system or C standard library, it demonstrates a detailed understanding of the ARM exception model, privilege levels, and memory management through the implementation of both serial communication and virtual memory.

## Overview

The system operates in a fully bare-metal environment and is emulated using QEMU's Raspberry Pi 2 model. It begins execution in EL1 (Privileged Kernel Mode), initializes UART0 for character output, sets up exception vectors, and handles mode switching to EL0 (User Mode). From there, it implements a system call interface using the `SVC` instruction to allow EL0-level programs to request services like printing to UART.

Following this, the project extends to configure and enable the Memory Management Unit (MMU). Section-level page tables are defined in memory, and virtual-to-physical address translation is activated using the Translation Table Base Register (TTBR), Domain Access Control Register (DACR), and System Control Register (SCTLR). The MMU ensures that EL0 user programs execute in isolated virtual memory regions, providing both protection and abstraction.

## Key Features

- **Bare-metal UART Driver**  
  A minimal UART0 interface is implemented for transmitting characters and strings using MMIO (Memory-Mapped I/O). A custom `printf`-like formatter is also provided, handling integer and string arguments using `stdarg.h`.

- **Exception-Level Transition**  
  The system transitions cleanly from EL1 to EL0 using proper stack and mode register configurations. EL0 is prevented from directly accessing hardware or privileged instructions.

- **System Call Interface (SVC)**  
  User-mode programs invoke system services using the Supervisor Call instruction. An SVC handler inspects the system call number and dispatches the corresponding kernel function securely.

- **Virtual Memory Support**  
  Implements a virtual memory subsystem using ARMv7-A’s MMU with section mappings. Identity and non-identity mappings are used to isolate kernel and user memory regions.

- **QEMU Emulation Target**  
  The project is designed to run on QEMU using `-M raspi2` with emulated serial output and memory behavior that matches the actual Raspberry Pi 2B hardware.

## Repository

GitHub: [Bare-metal UART & Virtual Memory OS (ARMv7-A AArch32)](https://github.com/manal-a7med/Bare-metal-UART-Virtual-Memory-OS-ARMv7-A-AArch32)

---

This project demonstrates low-level ARM OS development skills including serial communication, system call handling, and virtual memory management — all implemented and tested without an operating system.
