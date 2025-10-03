#ifndef SCREEN_H
#define SCREEN_H

#include "types.h"

void init_screen();
void clear_screen();
void print_char(char c);
void print_string(const char *str);
void print_hex(uint32_t n);
void set_cursor(int x, int y);
void scroll_screen();
void update_cursor();

#endif