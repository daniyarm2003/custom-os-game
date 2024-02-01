#ifndef _OS_TIMER_H
#define _OS_TIMER_H

#include "../include/basictypes.h"

#define TIMER_IRQ_NUMBER 0

#define PIT_FREQUENCY 1193182
#define TIMER_DEFAULT_FREQUENCY 1000

#define PIT_RW_MODE_READ 0
#define PIT_RW_MODE_LSB 1
#define PIT_RW_MODE_MSB 2
#define PIT_RW_MODE_LSB_MSB 3

typedef u32 timer_t;

typedef enum {
    PIT_MODE_TERMINAL_COUNT_INTERRUPT,
    PIT_MODE_HARDWARE_RETRIGGERABLE_ONE_SHOT,
    PIT_MODE_RATE_GENERATOR,
    PIT_MODE_SQUARE_WAVE_GENERATOR,
    PIT_MODE_SOFTWARE_STROBE,
    PIT_MODE_HARDWARE_STROBE
} PITMode;

void timer_init_handler();

void timer_set_frequency(timer_t frequency);
void sleep_for_timer_ticks(timer_t ticks);

#endif