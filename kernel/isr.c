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
#include "isr.h"
#include "screen.h"
#include "keyboard.h"
#include "timer.h"

void isr_handler(struct interrupt_frame *frame) {
    print_string("Interrupt: ");
    print_hex(frame->int_no);
    print_string("\n");
}

void irq_handler(struct interrupt_frame *frame) {
    if (frame->int_no >= 40) {
        outb(0xA0, 0x20); // Slave PIC EOI
    }
    outb(0x20, 0x20); // Master PIC EOI

    if (frame->int_no == 32) {
        timer_tick();
    } else if (frame->int_no == 33) {
        keyboard_handler();
    }
}

void init_isr() {
    // Remap PIC
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);
}