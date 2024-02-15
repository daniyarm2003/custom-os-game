#include "keyboard.h"
#include "ports.h"
#include "terminal.h"

#include "../include/basicmacros.h"
#include "../os/idt/isr.h"

bool scancodesPressed[NUM_SCANCODES] = {};

static void keyboard_handle_interrupt(ISRRegisters* regs) {
    UNUSED(regs);

    scancode_t portInput = port_inb(PORT_KEYBOARD_CONTROLLER_DATA);
    scancode_t scancode = portInput & KEYBOARD_SCANCODE_MASK;

    bool isPress = (portInput & KEYBOARD_RELEASE_MASK) == 0;
    scancodesPressed[scancode] = isPress;
}

void keyboard_init_handler() {
    irq_set_handler(KEYBOARD_IRQ_NUMBER, keyboard_handle_interrupt);
}

bool keyboard_is_scancode_pressed(scancode_t scancode) {
    return scancodesPressed[scancode];
}