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
#include "paging.h"
#include "memory.h"

uint32_t *page_directory = (uint32_t *)0x10000;
uint32_t *first_page_table = (uint32_t *)0x12000;

void init_paging() {
    for (int i = 0; i < 1024; i++) {
        page_directory[i] = 0x00000002; // Not present, writable
    }
    for (int i = 0; i < 1024; i++) {
        first_page_table[i] = (i * 0x1000) | 3; // Present, writable
    }
    page_directory[0] = (uint32_t)first_page_table | 3;
    asm volatile("mov %0, %%cr3" :: "r"(page_directory));
    asm volatile("mov %%cr0, %%eax; or $0x80000000, %%eax; mov %%eax, %%cr0" ::: "eax");
}