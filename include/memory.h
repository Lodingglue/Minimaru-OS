#ifndef MEMORY_H
#define MEMORY_H

#include "types.h"

void memcpy(void *dest, const void *src, uint32_t n);
void memset(void *dest, uint8_t val, uint32_t n);
uint32_t rand();
void outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port);

#endif