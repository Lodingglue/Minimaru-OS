#ifndef TIMER_H
#define TIMER_H

#include "types.h"

void init_timer();
void timer_tick();
uint32_t timer_get_ticks();

#endif