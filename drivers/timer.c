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
#include "timer.h"

static uint32_t ticks = 0;

void timer_tick() {
    ticks++;
}

uint32_t timer_get_ticks() {
    return ticks;
}

void init_timer() {
    outb(0x43, 0x36);
    outb(0x40, 0x9c);
    outb(0x40, 0x2e);
}