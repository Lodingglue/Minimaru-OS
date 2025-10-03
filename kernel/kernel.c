#include "kernel.h"
#include "gdt.h"
#include "idt.h"
#include "isr.h"
#include "paging.h"
#include "process.h"
#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "syscall.h"
#include "system.h"

void kernel_main() {
    print_string("Debug: Initializing GDT\n");
    init_gdt();
    print_string("Debug: Initializing IDT\n");
    init_idt();
    print_string("Debug: Initializing ISR\n");
    init_isr();
    print_string("Debug: Initializing paging\n");
    init_paging();
    print_string("Debug: Initializing processes\n");
    init_processes();
    print_string("Debug: Initializing screen\n");
    init_screen();
    print_string("Debug: Initializing keyboard\n");
    init_keyboard();
    print_string("Debug: Initializing timer\n");
    init_timer();
    print_string("Debug: Initializing syscalls\n");
    init_syscalls();
    print_string("Debug: Enabling interrupts\n");
    asm volatile("sti"); // Enable interrupts
    print_string("Debug: Starting shell\n");
    start_shell();
    while (1) {
        asm("hlt");
    }
}