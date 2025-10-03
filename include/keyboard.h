#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "types.h"

#define KEY_ENTER 0x1C
#define KEY_BACKSPACE 0x0E
#define KEY_SPACE 0x39
#define KEY_CAPSLOCK 0x3A
#define KEY_LSHIFT 0x2A
#define KEY_RSHIFT 0x36
#define KEY_LSHIFT_RELEASE 0xAA
#define KEY_RSHIFT_RELEASE 0xB6

void init_keyboard();
void keyboard_handler();
void get_line(char *buffer, int size);
char read_key();

#endif