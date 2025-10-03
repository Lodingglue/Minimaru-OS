; Bootloader for Minimal OS
[bits 32]
[extern kernel_main]

section .multiboot
align 4
dd 0x1BADB002           ; Magic number
dd 0x00                 ; Flags
dd -(0x1BADB002 + 0x00) ; Checksum

section .text
global _start
_start:
    cli                 ; Disable interrupts
    mov esp, stack_top  ; Set up stack
    call kernel_main     ; Call kernel entry point
    hlt                 ; Halt CPU

section .bss
align 16
stack_bottom:
    resb 16384         ; 16KB stack
stack_top: