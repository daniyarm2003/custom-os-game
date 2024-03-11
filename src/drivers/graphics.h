#ifndef _OS_GRAPHICS_H
#define _OS_GRAPHICS_H

#include "../graphics/color.h"
#include "../graphics/image.h"

#define GRAPHICS_IMAGE_MIN_ALPHA 0x10

void graphics_init(multiboot_info_t* mBootInfo);
void graphics_terminate();

graphics_pos_t graphics_get_width();
graphics_pos_t graphics_get_height();

void graphics_draw_pixel(graphics_pos_t x, graphics_pos_t y, Color color);
void graphics_draw_rectangle(graphics_pos_t x, graphics_pos_t y, graphics_pos_t width, graphics_pos_t height, Color color);

void graphics_draw_image(graphics_pos_t x, graphics_pos_t y, const Image* image);
void graphics_draw_image_scaled(graphics_pos_t x, graphics_pos_t y, graphics_pos_t width, graphics_pos_t height, const Image* image);

void graphics_clear_buffer();
void graphics_update_buffer();

#endif