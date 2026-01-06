#ifndef TIMER_H
#define TIMER_H

#include "types.h"

typedef void (*timer_callback_t)(void);

typedef struct timer_node {
    uint32_t expire_tick;
    timer_callback_t callback;
    uint32_t intercval_ticks;
    struct time_node *next;
} timer_note_t;

void add_timer(uint32_t delay_ticks, timer_callback_t timer_callback_t, uint32_t interval_ticks);
void remove_timer(timer_callback_t callback);
void init_timer_system(void);


void init_timer(uint32_t freq);

#endif
