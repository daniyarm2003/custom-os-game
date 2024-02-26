#include "color.h"

static u8 framebufferType;

static u8 redMaskSize, redShiftOffset;
static u8 greenMaskSize, greenShiftOffset;
static u8 blueMaskSize, blueShiftOffset;

void color_lib_init(multiboot_info_t* mBootInfo) {
    framebufferType = mBootInfo->framebuffer_type;
    
    redMaskSize = mBootInfo->framebuffer_red_mask_size;
    redShiftOffset = mBootInfo->framebuffer_red_field_position;

    greenMaskSize = mBootInfo->framebuffer_green_mask_size;
    greenShiftOffset = mBootInfo->framebuffer_green_field_position;

    blueMaskSize = mBootInfo->framebuffer_blue_mask_size;
    blueShiftOffset = mBootInfo->framebuffer_blue_field_position;
}

pixel_t color_to_framebuffer_value(Color color) {
    switch(framebufferType) {
        case MULTIBOOT_FRAMEBUFFER_TYPE_RGB:

            u8 redValue = (color.rgb.red >> (8 - redMaskSize)) & ((1 << redMaskSize) - 1);
            u8 greenValue = (color.rgb.green >> (8 - greenMaskSize)) & ((1 << greenMaskSize) - 1);
            u8 blueValue = (color.rgb.blue >> (8 - blueMaskSize)) & ((1 << blueMaskSize) - 1);

            pixel_t framebufferValue = ((pixel_t)redValue << redShiftOffset) | ((pixel_t)greenValue << greenShiftOffset) | ((pixel_t)blueValue << blueShiftOffset);

            return framebufferValue;

        default:
            break;
    }

    return 0;
}