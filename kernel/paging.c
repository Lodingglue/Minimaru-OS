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