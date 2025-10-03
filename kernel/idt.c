#include "idt.h"
#include "isr.h"
#include "syscall.h"

struct idt_entry {
    uint16_t base_low;
    uint16_t sel;
    uint8_t always0;
    uint8_t flags;
    uint16_t base_high;
} __attribute__((packed));

struct idt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

struct idt_entry idt[256];
struct idt_ptr idtp;

extern void idt_flush(uint32_t);

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt[num].base_low = base & 0xFFFF;
    idt[num].base_high = (base >> 16) & 0xFFFF;
    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}

void init_idt() {
    idtp.limit = (sizeof(struct idt_entry) * 256) - 1;
    idtp.base = (uint32_t)&idt;

    // Zero out IDT
    for (int i = 0; i < 256; i++) {
        idt_set_gate(i, 0, 0, 0); // Clear all entries
    }

    // Set ISR gates (0-31 for CPU exceptions)
    for (int i = 0; i < 32; i++) {
        idt_set_gate(i, (uint32_t)isr0 + i * 16, 0x08, 0x8E);
    }

    // Set IRQ gates (32-47 for IRQs)
    idt_set_gate(32, (uint32_t)irq0, 0x08, 0x8E); // Timer
    idt_set_gate(33, (uint32_t)irq1, 0x08, 0x8E); // Keyboard

    // Set syscall gate
    idt_set_gate(128, (uint32_t)syscall_int, 0x08, 0x8E);

    idt_flush((uint32_t)&idtp);
}