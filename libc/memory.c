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
#include "memory.h"

void memcpy(void *dest, const void *src, uint32_t n) {
    uint8_t *d = (uint8_t *)dest;
    uint8_t *s = (uint8_t *)src;
    for (uint32_t i = 0; i < n; i++) {
        d[i] = s[i];
    }
}

void memset(void *dest, uint8_t val, uint32_t n) {
    uint8_t *d = (uint8_t *)dest;
    for (uint32_t i = 0; i < n; i++) {
        d[i] = val;
    }
}

uint32_t rand() {
    static uint32_t seed = 12345;
    seed = seed * 1103515245 + 12345;
    return (seed >> 16) & 0x7FFF;
}

void outb(uint16_t port, uint8_t val) {
    asm volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}