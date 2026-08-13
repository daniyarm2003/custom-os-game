#include "controls.h"
#include "../drivers/keyboard.h"
#include "../drivers/scancodes.h"

bool controls_is_left_control_pressed() {
    return keyboard_is_scancode_pressed(SCANCODE_LEFT_ARROW) || keyboard_is_scancode_pressed(SCANCODE_A);
}

bool controls_is_right_control_pressed() {
    return keyboard_is_scancode_pressed(SCANCODE_RIGHT_ARROW) || keyboard_is_scancode_pressed(SCANCODE_D);
}

bool controls_is_jump_control_pressed() {
    return keyboard_is_scancode_pressed(SCANCODE_SPACE) || keyboard_is_scancode_pressed(SCANCODE_W) || keyboard_is_scancode_pressed(SCANCODE_UP_ARROW);
}