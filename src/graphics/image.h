#ifndef _OS_IMAGE_H
#define _OS_IMAGE_H

#include "../include/basictypes.h"
#include "types.h"

#define BYTES_PER_PIXEL_RGB 3
#define BYTES_PER_PIXEL_RGBA 4

typedef struct image_t {
    graphics_pos_t width, height;
    u8 bytesPerPixel;
    const char* imageData;
} Image;

#endif