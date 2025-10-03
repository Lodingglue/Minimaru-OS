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

#include "kernel.h"
#include "gdt.h"
#include "idt.h"
#include "isr.h"
#include "paging.h"
#include "process.h"
#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "syscall.h"
#include "system.h"

void kernel_main() {
    print_string("Debug: Initializing GDT\n");
    init_gdt();
    print_string("Debug: Initializing IDT\n");
    init_idt();
    print_string("Debug: Initializing ISR\n");
    init_isr();
    print_string("Debug: Initializing paging\n");
    init_paging();
    print_string("Debug: Initializing processes\n");
    init_processes();
    print_string("Debug: Initializing screen\n");
    init_screen();
    print_string("Debug: Initializing keyboard\n");
    init_keyboard();
    print_string("Debug: Initializing timer\n");
    init_timer();
    print_string("Debug: Initializing syscalls\n");
    init_syscalls();
    print_string("Debug: Enabling interrupts\n");
    asm volatile("sti"); // Enable interrupts
    print_string("Debug: Starting shell\n");
    start_shell();
    while (1) {
        asm("hlt");
    }
}