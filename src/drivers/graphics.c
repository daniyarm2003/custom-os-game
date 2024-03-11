#include "graphics.h"

#include "../lib/memory.h"
#include "../include/basicmacros.h"

static graphics_pos_t width, height;
static size_t bytesPerPixel;

static volatile u8* frameBufferAddr;
static u8* frameDoubleBufferAddr;

void graphics_init(multiboot_info_t* mBootInfo) {
    color_lib_init(mBootInfo);

    width = mBootInfo->framebuffer_pitch / (mBootInfo->framebuffer_bpp / 8);
    height = mBootInfo->framebuffer_height;

    bytesPerPixel = (size_t)mBootInfo->framebuffer_bpp / 8;

    frameBufferAddr = (volatile u8*)(uintptr_t)mBootInfo->framebuffer_addr;
    frameDoubleBufferAddr = (u8*)malloc(mBootInfo->framebuffer_pitch * mBootInfo->framebuffer_height);
}

void graphics_terminate() {
    free(frameDoubleBufferAddr);
}

graphics_pos_t graphics_get_width() {
    return width;
}

graphics_pos_t graphics_get_height() {
    return height;
}

void graphics_draw_pixel(graphics_pos_t x, graphics_pos_t y, Color color) {
    pixel_t colorValue = color_to_framebuffer_value(color);

    graphics_pos_t clampedX = CLAMP(x, 0, width - 1);
    graphics_pos_t clampedY = CLAMP(y, 0, height - 1);

    for(size_t i = 0; i < bytesPerPixel; i++) {
        frameDoubleBufferAddr[(clampedY * width + clampedX) * bytesPerPixel + i] = (u8)(colorValue >> (8 * i));
    }
}

void graphics_draw_rectangle(graphics_pos_t x, graphics_pos_t y, graphics_pos_t recWidth, graphics_pos_t recHeight, Color color) {
    pixel_t colorValue = color_to_framebuffer_value(color);

    for(graphics_pos_t yPos = CLAMP(y, 0, height - 1); yPos < CLAMP(y + recHeight, 0, height - 1); yPos++) {
        for(graphics_pos_t xPos = CLAMP(x, 0, width - 1); xPos < CLAMP(x + recWidth, 0, width - 1); xPos++) {
            for(size_t i = 0; i < bytesPerPixel; i++) {
                frameDoubleBufferAddr[(yPos * width + xPos) * bytesPerPixel + i] = (u8)(colorValue >> (8 * i));
            }
        }
    }
}

void graphics_draw_image(graphics_pos_t x, graphics_pos_t y, const Image* image) {
    for(graphics_pos_t yPos = CLAMP(y, 0, height - 1); yPos < CLAMP(y + image->height, 0, height - 1); yPos++) {
        for(graphics_pos_t xPos = CLAMP(x, 0, width - 1); xPos < CLAMP(x + image->width, 0, width - 1); xPos++) {

            size_t imageDataIndex = (size_t)(((yPos - y) * image->width + (xPos - x)) * image->bytesPerPixel);

            if(image->bytesPerPixel == BYTES_PER_PIXEL_RGBA) {
                u8 alphaValue = image->imageData[imageDataIndex + 3];

                if(alphaValue < GRAPHICS_IMAGE_MIN_ALPHA) {
                    continue;
                }
            }

            Color pixelColor;

            pixelColor.rgb.red = image->imageData[imageDataIndex + 0];
            pixelColor.rgb.green = image->imageData[imageDataIndex + 1];
            pixelColor.rgb.blue = image->imageData[imageDataIndex + 2];

            graphics_draw_pixel(xPos, yPos, pixelColor);
        }
    }
}

void graphics_draw_image_scaled(graphics_pos_t x, graphics_pos_t y, graphics_pos_t imgWidth, graphics_pos_t imgHeight, const Image* image) {
    for(graphics_pos_t yPos = CLAMP(y, 0, height - 1); yPos < CLAMP(y + imgHeight, 0, height - 1); yPos++) {
        for(graphics_pos_t xPos = CLAMP(x, 0, width - 1); xPos < CLAMP(x + imgWidth, 0, width - 1); xPos++) {

            f32 imgXPos = (f32)(xPos - x) * (f32)image->width / (f32)imgWidth;
            f32 imgYPos = (f32)(yPos - y) * (f32)image->height / (f32)imgHeight;

            size_t imageDataIndex = (size_t)(((graphics_pos_t)imgYPos * image->width + (graphics_pos_t)imgXPos) * image->bytesPerPixel);

            if(image->bytesPerPixel == BYTES_PER_PIXEL_RGBA) {
                u8 alphaValue = image->imageData[imageDataIndex + 3];

                if(alphaValue < GRAPHICS_IMAGE_MIN_ALPHA) {
                    continue;
                }
            }

            Color pixelColor;

            pixelColor.rgb.red = image->imageData[imageDataIndex + 0];
            pixelColor.rgb.green = image->imageData[imageDataIndex + 1];
            pixelColor.rgb.blue = image->imageData[imageDataIndex + 2];

            graphics_draw_pixel(xPos, yPos, pixelColor);
        }
    }
}

void graphics_clear_buffer() {
    memzero(frameDoubleBufferAddr, width * height * bytesPerPixel);
}

void graphics_update_buffer() {
    memcpy_v(frameBufferAddr, frameDoubleBufferAddr, width * height * bytesPerPixel);
}