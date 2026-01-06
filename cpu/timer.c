#include "timer.h"
#include "../libc/string.h"
#include "isr.h"
#include "../libc/function.h"
#include "ports.h"
#include <stdint.h>
#include "../libc/mem.h"

static timer_note_t *timer_list = NULL;
uint32_t tick = 0;

void init_timer_system() {
    timer_list = NULL;
}

static void timer_callback(registers_t *regs) {
    tick++;
    //kprint("Tick: ");
    
    timer_note_t **curr = &timer_list;
    while(*curr != NULL) {
        if(tick >= (*curr)->expire_tick) {
            (*curr)->callback();

            timer_note_t *to_remove = *curr;
            if((*curr)->intercval_ticks > 0) {
                to_remove->expire_tick = tick + to_remove->intercval_ticks;
                curr = &(*curr)->next;
            } else {
                *curr = to_remove->next;
            }
        } else {
            curr = &(*curr)->next;
        }
    }

    //char tick_ascii[256];
    //int_to_ascii(tick, tick_ascii);
    //kprint(tick_ascii);
    //kprint("\n");
    
    UNUSED(regs);
}

void add_timer(uint32_t delay_ticks, timer_callback_t callback, uint32_t interval_ticks) {
    timer_note_t *new_timer = kmalloc(sizeof(timer_note_t),0,&new_timer);
    new_timer->expire_tick = tick + delay_ticks;
    new_timer->callback = callback;
    new_timer->intercval_ticks = interval_ticks;

    new_timer->next = timer_list;
    timer_list = new_timer;
}

void init_timer(uint32_t freq) {
    /* Install the function we just wrote */
    register_interrupt_handler(IRQ0, timer_callback);

    /* Get the PIT value: hardware clock at 1193180 Hz */
    uint32_t divisor = 1193180 / freq;
    uint8_t low  = (uint8_t)(divisor & 0xFF);
    uint8_t high = (uint8_t)( (divisor >> 8) & 0xFF);
    /* Send the command */
    port_byte_out(0x43, 0x36); /* Command port */
    port_byte_out(0x40, low);
    port_byte_out(0x40, high);

    init_timer_system();
}

