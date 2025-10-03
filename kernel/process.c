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