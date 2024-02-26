#ifndef _OS_COLOR_H
#define _OS_COLOR_H

#include "../graphics/types.h"
#include "../include/multiboot.h"

typedef union color_t {
    struct {
        u8 blue;
        u8 green;
        u8 red;
        u8 alpha;
    } rgb;
    u32 value;
} Color;

void color_lib_init(multiboot_info_t* mBootInfo);
pixel_t color_to_framebuffer_value(Color color);

#endif