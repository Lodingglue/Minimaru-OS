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



#include "keyboard.h"
#include "screen.h"
#include "string.h"

static char key_buffer[256];
static int buffer_index = 0;
static int enter_pressed = 0;
static int capslock_active = 0;
static int shift_pressed = 0;

static const char scancode_to_ascii[] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
    0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
    '*', 0, ' '
};

static const char scancode_to_ascii_shift[] = {
    0, 27, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b',
    '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',
    0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~',
    0, '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0,
    '*', 0, ' '
};

static char to_upper(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - 32;
    }
    return c;
}

char read_key() {
    uint8_t scancode = inb(0x60);
    if (scancode & 0x80) { // Ignore key release
        if (scancode == (KEY_LSHIFT_RELEASE & 0x7F) || scancode == (KEY_RSHIFT_RELEASE & 0x7F)) {
            shift_pressed = 0;
        }
        return 0;
    }
    if (scancode == KEY_CAPSLOCK) {
        capslock_active = !capslock_active;
        return 0;
    }
    if (scancode == KEY_LSHIFT || scancode == KEY_RSHIFT) {
        shift_pressed = 1;
        return 0;
    }
    if (scancode < sizeof(scancode_to_ascii)) {
        char c;
        if (shift_pressed) {
            c = scancode_to_ascii_shift[scancode];
        } else {
            c = scancode_to_ascii[scancode];
            if (capslock_active && c >= 'a' && c <= 'z') {
                c = to_upper(c);
            }
        }
        return c;
    }
    return 0;
}

void keyboard_handler() {
    char c = read_key();
    if (c) {
        /* Commented out debug logging
        print_string("Scancode processed: ");
        print_hex(inb(0x60)); // Debug: Show raw scancode
        print_string(" -> ASCII: ");
        print_hex(c);
        print_string("\n");
        */
        if (c == '\n') {
            key_buffer[buffer_index] = 0; // Null-terminate
            enter_pressed = 1; // Signal line completion
            print_string("Enter detected, buffer: ");
            print_string(key_buffer);
            print_string("\n");
        } else if (c == '\b' && buffer_index > 0) {
            buffer_index--;
            key_buffer[buffer_index] = 0;
            print_string("\b \b"); // Erase character
        } else if (c >= ' ' && buffer_index < sizeof(key_buffer) - 1) {
            key_buffer[buffer_index++] = c;
            print_char(c); // Echo to screen
        }
    }
}

void init_keyboard() {
    buffer_index = 0;
    enter_pressed = 0;
    capslock_active = 0;
    shift_pressed = 0;
}

void get_line(char *buffer, int size) {
    enter_pressed = 0;
    buffer_index = 0;
    key_buffer[0] = 0;
    while (!enter_pressed) {
        asm("hlt"); // Wait for keyboard interrupt
    }
    /* Commented out debug logging
    // print_string("Debug: key_buffer before copy: [");
    // print_string(key_buffer);
    // print_string("]\n");
    */
    // Manual copy instead of strncpy
    int i;
    for (i = 0; i < size - 1 && key_buffer[i] != 0; i++) {
        buffer[i] = key_buffer[i];
    }
    buffer[i] = 0; // Null-terminate
    /* Commented out debug logging
    // print_string("Debug: buffer after copy: [");
    // print_string(buffer);
    // print_string("]\n");
    */
    enter_pressed = 0; // Reset for next call
    print_string("Line read: ");
    print_string(buffer);
    print_string("\n");
}