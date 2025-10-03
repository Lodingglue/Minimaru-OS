#ifndef ISR_H
#define ISR_H

#include "types.h"

struct interrupt_frame {
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;
};

void init_isr();
void isr_handler(struct interrupt_frame *frame);
void irq_handler(struct interrupt_frame *frame);

extern void isr0();
extern void isr1();
// ... (Declare ISRs up to isr31)
extern void isr31();
extern void irq0();
extern void irq1();

#endif