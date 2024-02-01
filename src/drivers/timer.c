#include "timer.h"
#include "ports.h"

#include "../os/idt/isr.h"
#include "../include/basicmacros.h"

static timer_t globalTimer = 0;

static u8 timer_get_command_byte(PITMode mode) {
    return (PIT_RW_MODE_LSB_MSB << 4) | (((u8)mode & 0x7) << 1);
}

static void timer_handle_interrupt(ISRRegisters* regs) {
    UNUSED(regs);
    globalTimer++;
}

void timer_init_handler() {
    timer_set_frequency(TIMER_DEFAULT_FREQUENCY);
    irq_set_handler(TIMER_IRQ_NUMBER, timer_handle_interrupt);
}

void timer_set_frequency(timer_t frequency) {
    u8 commandByte = timer_get_command_byte(PIT_MODE_SQUARE_WAVE_GENERATOR);
    timer_t divisor = PIT_FREQUENCY / frequency;

    port_outb(PORT_PIT_COMMAND, commandByte);

    port_outb(PORT_PIT_CHANNEL0, (u8)(divisor & 0xFF));
    port_outb(PORT_PIT_CHANNEL0, (u8)((divisor >> 8) & 0xFF));
}

void sleep_for_timer_ticks(timer_t ticks) {
    timer_t sleepUntil = globalTimer + ticks;

    while(globalTimer != sleepUntil) {
        asm volatile (
            "hlt"
        );
    }
}