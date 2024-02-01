#ifndef _OS_KEYBOARD_H
#define _OS_KEYBOARD_H

#include "../include/basictypes.h"

#define KEYBOARD_IRQ_NUMBER 0x1

#define KEYBOARD_SCANCODE_MASK 0x7F
#define KEYBOARD_RELEASE_MASK (~KEYBOARD_SCANCODE_MASK)

#define NUM_SCANCODES (KEYBOARD_SCANCODE_MASK + 1)

typedef u8 scancode_t;

void keyboard_init_handler();

bool keyboard_is_scancode_pressed(scancode_t scancode);

#endif