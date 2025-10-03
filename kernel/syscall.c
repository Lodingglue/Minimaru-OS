#include "syscall.h"
#include "screen.h"
#include "process.h"
#include "system.h"
#include "idt.h"

void syscall_handler(struct interrupt_frame *frame) {
    switch (frame->eax) {
        case 0: // Print
            print_string((char *)frame->ebx);
            break;
        case 1: // Snake
            print_string("Debug: Snake syscall reached\n");
            snake_main();
            break;
        case 2: // Memory info
            print_string("Heap: 1MB\n");
            break;
        case 3: // Process list
            for (int i = 0; i < 32; i++) {
                if (processes[i].state == 1) {
                    print_string("PID: ");
                    print_hex(i);
                    print_string("\n");
                }
            }
            break;
        case 4: // Halt
            asm("hlt");
            break;
    }
}

void init_syscalls() {
    print_string("Debug: Initializing syscalls\n");
    idt_set_gate(128, (uint32_t)syscall_int, 0x08, 0x8E);
}