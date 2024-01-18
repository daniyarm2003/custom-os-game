#include "terminal.h"
#include "ports.h"

#include "../lib/string.h"
#include "../lib/memory.h"

#include "../include/basicmacros.h"

#include <stdarg.h>

static volatile u16* const vgaMemory = (volatile u16*)VGA_MEMORY_ADDRESS;
static cursor_t cursor = 0;

static VGAColor foregroundColor = VGA_WHITE;
static VGAColor backgroundColor = VGA_BLACK;

static u8 terminal_get_color_byte() {
    return ((u8)backgroundColor << 4) | (u8)foregroundColor;
}

static void terminal_fill_bottom_rows(cursor_t rows) {
    if(rows < 0) {
        return;
    }

    u16 fill = ((u16)terminal_get_color_byte() << 8) | ' ';
    cursor_t fillRows = MIN(rows, VGA_HEIGHT);
    
    for(cursor_t i = VGA_WIDTH * (VGA_HEIGHT - fillRows); i < VGA_WIDTH * VGA_HEIGHT; i++) {
        vgaMemory[i] = fill;
    }
}

void terminal_init() {
    terminal_set_foreground_color(VGA_WHITE);
    terminal_set_background_color(VGA_BLACK);

    terminal_fill_bottom_rows(VGA_HEIGHT);
}

void terminal_set_foreground_color(VGAColor color) {
    foregroundColor = color;
}

void terminal_set_background_color(VGAColor color) {
    backgroundColor = color;
}

cursor_t terminal_get_cursor_pos() {
    return cursor;
}

static void terminal_update_vga_cursor() {
    port_outb(PORT_VGA_CONTROL_REGISTER, VGA_CONTROL_CURSOR_LOW_BYTE);
    port_outb(PORT_VGA_DATA_REGISTER, cursor & 0xFF);

    port_outb(PORT_VGA_CONTROL_REGISTER, VGA_CONTROL_CURSOR_HIGH_BYTE);
    port_outb(PORT_VGA_DATA_REGISTER, (cursor >> 8) & 0xFF);
}

static void terminal_scroll_raw(cursor_t lines) {
    if(lines <= 0) {
        return;
    }

    if(lines < VGA_HEIGHT) {
        memcpy_v(&vgaMemory[0], &vgaMemory[VGA_WIDTH * lines], sizeof(u16) * VGA_WIDTH * (VGA_HEIGHT - lines));
    }

    terminal_fill_bottom_rows(lines);
    cursor -= VGA_WIDTH * lines;
}

void terminal_scroll(cursor_t lines) {
    terminal_scroll_raw(lines);
    terminal_update_vga_cursor();
}

static void terminal_set_cursor_pos_raw(cursor_t pos) {
    if(pos < 0) {
        return;
    }

    cursor = pos;

    if(cursor >= VGA_WIDTH * VGA_HEIGHT) {
        terminal_scroll_raw((cursor - VGA_WIDTH * VGA_HEIGHT) / VGA_WIDTH + 1);
    }
}

void terminal_set_cursor_pos(cursor_t pos) {
    terminal_set_cursor_pos_raw(pos);
    terminal_update_vga_cursor();
}

static void terminal_offset_cursor_pos_raw(cursor_t offset) {
    terminal_set_cursor_pos_raw(cursor + offset);
}

void terminal_offset_cursor_pos(cursor_t offset) {
    terminal_offset_cursor_pos_raw(offset);
    terminal_update_vga_cursor();
}

cursor_t terminal_get_cursor_x() {
    return cursor % VGA_WIDTH;
}

cursor_t terminal_get_cursor_y() {
    return cursor / VGA_WIDTH;
}

static void terminal_print_carriage_return() {
    cursor_t y = terminal_get_cursor_y();
    terminal_set_cursor_pos_raw(VGA_WIDTH * y);
}

static void terminal_print_newline() {
    cursor_t y = terminal_get_cursor_y() + 1;
    terminal_set_cursor_pos_raw(VGA_WIDTH * y);
}

static void terminal_print_char_raw(char ch) {
    u8 colorByte = terminal_get_color_byte();

    switch (ch) {
    case '\b':

        terminal_offset_cursor_pos_raw(-1);
        vgaMemory[cursor] = ((u16)colorByte) | ' ';

        break;

    case '\r':

        terminal_print_carriage_return();
        break;

    case '\n':
        
        terminal_print_newline();
        break;

    default:

        vgaMemory[cursor] = ((u16)colorByte << 8) | ch;
        terminal_offset_cursor_pos_raw(1);

        break;
    }
}

void terminal_print_char(char ch) {
    terminal_print_char_raw(ch);
    terminal_update_vga_cursor();
}

static void terminal_print_string_raw(const char* str) {
    for(const char* chPtr = str; *chPtr; chPtr++) {
        terminal_print_char_raw(*chPtr);
    }
}

void terminal_print_string(const char* str) {
    terminal_print_string_raw(str);
    terminal_update_vga_cursor();
}

static void terminal_print_uint_raw(u32 num) {
    char numBuffer[16];
    size_t numBufferSize = 0;

    if(num == 0) {
        terminal_print_char_raw('0');
        return;
    }

    while(num != 0) {
        numBuffer[numBufferSize++] = (char)(num % 10) + '0';
        num /= 10;
    }

    while(numBufferSize != 0) {
        terminal_print_char_raw(numBuffer[--numBufferSize]);
    }
}

void terminal_print_uint(u32 num) {
    terminal_print_uint_raw(num);
    terminal_update_vga_cursor();
}

static void terminal_print_int_raw(s32 num) {
    if(num < 0) {
        num = -num;
        terminal_print_char_raw('-');
    }

    terminal_print_uint_raw((u32)num);
}

void terminal_print_int(s32 num) {
    terminal_print_int_raw(num);
    terminal_update_vga_cursor();
}

void terminal_printf(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    bool formatting = false;

    for(const char* chPtr = fmt; *chPtr; chPtr++) {
        if(formatting) {
            formatting = false;

            switch(*chPtr) {
                case 'c':

                    char charArg = (char)va_arg(args, int);
                    terminal_print_char_raw(charArg);

                    break;

                case 's':

                    const char* strArg = va_arg(args, const char*);
                    terminal_print_string_raw(strArg);

                    break;

                case 'd':

                    s32 intArg = va_arg(args, s32);
                    terminal_print_int_raw(intArg);

                    break;

                default:

                    terminal_print_char_raw(*chPtr);
                    break;
            }
        }
        else if(*chPtr == '%') {
            formatting = true;
        }
        else {
            terminal_print_char_raw(*chPtr);
        }
    }

    terminal_update_vga_cursor();
    va_end(args);
}