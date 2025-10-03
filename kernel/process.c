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
#include "process.h"
#include "memory.h"

struct process processes[32]; // Define processes array
int current_pid = 0;

void init_processes() {
    for (int i = 0; i < 32; i++) {
        processes[i].state = 0; // Inactive
    }
    processes[0].state = 1; // Shell process
    processes[0].pid = 0;
}

void schedule() {
    for (int i = 0; i < 32; i++) {
        if (processes[i].state == 1) {
            current_pid = i;
            return;
        }
    }
}