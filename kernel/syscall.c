/*
 * Copyright (C) 2025 Lodingglue
 *
 * This file is part of Minimaru-OS.
 *
 * Minimaru-OS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Minimaru-OS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Minimaru-OS.  If not, see <https://www.gnu.org/licenses/>.
 */
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