#ifndef PROCESS_H
#define PROCESS_H

#include "types.h"

struct process {
    int pid;
    int state; // 0: inactive, 1: active
};

extern struct process processes[32]; // Declare processes array

void init_processes();
void schedule();

#endif