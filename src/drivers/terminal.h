#ifndef _OS_TERMINAL_H
#define _OS_TERMINAL_H

#include "../include/basictypes.h"

#define VGA_MEMORY_ADDRESS 0xB8000

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

#define VGA_CONTROL_CURSOR_LOW_BYTE 0xF
#define VGA_CONTROL_CURSOR_HIGH_BYTE 0xE

typedef enum {
    VGA_BLACK,
    VGA_BLUE,
    VGA_GREEN,
    VGA_CYAN,
    VGA_RED,
    VGA_PURPLE,
    VGA_BROWN,
    VGA_LIGHT_GREY,
    VGA_GREY,
    VGA_LIGHT_BLUE,
    VGA_LIGHT_GREEN,
    VGA_LIGHT_CYAN,
    VGA_LIGHT_RED,
    VGA_MAGENTA,
    VGA_YELLOW,
    VGA_WHITE
} VGAColor;

typedef s16 cursor_t;

void terminal_init();

void terminal_set_background_color(VGAColor color);
void terminal_set_foreground_color(VGAColor color);

cursor_t terminal_get_cursor_pos();

void terminal_set_cursor_pos(cursor_t pos);
void terminal_offset_cursor_pos(cursor_t pos);

cursor_t terminal_get_cursor_x();
cursor_t terminal_get_cursor_y();

void terminal_scroll(cursor_t lines);

void terminal_print_char(char ch);
void terminal_print_string(const char* str);

void terminal_print_uint(u32 num);
void terminal_print_int(s32 num);

void terminal_printf(const char* fmt, ...);

#endif