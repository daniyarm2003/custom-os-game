#include "lib/string.h"
#include "lib/memory.h"
#include "include/basicmacros.h"
#include "include/multiboot.h"
#include "drivers/terminal.h"
#include "os/idt/idt.h"
#include "drivers/timer.h"
#include "os/include/linker_symbols.h"

void kmain(multiboot_info_t* mBootInfo, u32 magic) {
    UNUSED(magic);

    idt_init();
    terminal_init();

    memory_manager_init(mBootInfo);

    uintptr_t frameBufferAddr = (uintptr_t)mBootInfo->framebuffer_addr;

    bool drawBlue = false;

    while(true) {
        for(u32 i = 0; i < 800 * 600; i++) {
            u32* pixelAddr = (u32*)(frameBufferAddr + 4 * i);
            u32 pixel = drawBlue ? ((1 << mBootInfo->framebuffer_blue_mask_size) - 1) << mBootInfo->framebuffer_blue_field_position
                : ((1 << mBootInfo->framebuffer_red_mask_size) - 1) << mBootInfo->framebuffer_red_field_position;

            *pixelAddr = pixel;
        }

        sleep_for_timer_ticks(1000);

        drawBlue = !drawBlue;
    }
}