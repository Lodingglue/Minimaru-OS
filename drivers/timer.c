#include "timer.h"

static uint32_t ticks = 0;

void timer_tick() {
    ticks++;
}

uint32_t timer_get_ticks() {
    return ticks;
}

void init_timer() {
    // Set PIT to ~100Hz (1193180 / 11932)
    outb(0x43, 0x36);
    outb(0x40, 0x9c);
    outb(0x40, 0x2e);
}