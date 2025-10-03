#ifndef SYSCALL_H
#define SYSCALL_H

#include "types.h"
#include "isr.h"

extern void syscall_int(); // Declare syscall_int
void init_syscalls();
void syscall_handler(struct interrupt_frame *frame);

#endif