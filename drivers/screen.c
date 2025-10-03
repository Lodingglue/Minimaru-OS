#include "screen.h"
#include "memory.h"

uint16_t *video_memory = (uint16_t *)0xB8000;
int cursor_x = 0;
int cursor_y = 0;
static int screen_initialized = 0;

void clear_screen() {
    for (int i = 0; i < 80 * 25; i++) {
        video_memory[i] = (0x07 << 8) | ' ';
    }
    cursor_x = 0;
    cursor_y = 0;
    if (screen_initialized) {
        update_cursor();
    }
}

void print_char(char c) {
    // Always initialize cursor for early writes
    if (cursor_x == 0 && cursor_y == 0 && !screen_initialized) {
        for (int i = 0; i < 80 * 25; i++) {
            video_memory[i] = (0x07 << 8) | ' ';
        }
    }
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
    } else {
        video_memory[cursor_y * 80 + cursor_x] = (0x07 << 8) | c;
        cursor_x++;
    }
    if (cursor_x >= 80) {
        cursor_x = 0;
        cursor_y++;
    }
    if (cursor_y >= 25) {
        scroll_screen();
    }
    if (screen_initialized) {
        update_cursor();
    }
}

void print_string(const char *str) {
    while (*str) {
        print_char(*str++);
    }
}

void scroll_screen() {
    memcpy(video_memory, video_memory + 80, 80 * 24 * 2);
    for (int i = 80 * 24; i < 80 * 25; i++) {
        video_memory[i] = (0x07 << 8) | ' ';
    }
    cursor_y--;
}

void update_cursor() {
    uint16_t pos = cursor_y * 80 + cursor_x;
    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}

void set_cursor(int x, int y) {
    cursor_x = x;
    cursor_y = y;
    if (screen_initialized) {
        update_cursor();
    }
}

void print_hex(uint32_t n) {
    char buf[9];
    for (int i = 7; i >= 0; i--) {
        int nibble = (n >> (i * 4)) & 0xF;
        buf[7 - i] = nibble < 10 ? nibble + '0' : nibble - 10 + 'A';
    }
    buf[8] = 0;
    print_string("0x");
    print_string(buf);
}

void init_screen() {
    clear_screen();
    screen_initialized = 1;
}