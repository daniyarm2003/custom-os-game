#include "lib/string.h"
#include "lib/memory.h"
#include "include/basicmacros.h"
#include "include/multiboot.h"
#include "drivers/terminal.h"
#include "os/idt/idt.h"
#include "drivers/timer.h"
#include "os/include/linker_symbols.h"
#include "drivers/graphics.h"
#include "lib/math.h"

void kmain(multiboot_info_t* mBootInfo, u32 magic) {
    UNUSED(magic);

    idt_init();
    terminal_init();

    memory_manager_init(mBootInfo);
    graphics_init(mBootInfo);

    Color testCol;

    testCol.rgb.red = 0x00;
    testCol.rgb.green = 0x80;
    testCol.rgb.blue = 0xFF;

    while(true) {
        graphics_clear_buffer();

        graphics_draw_rectangle(50, 50, 200, 300, testCol);

        graphics_update_buffer();

        sleep_for_timer_ticks(10);
    }

    graphics_terminate();
}