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
#include "images/images.h"
#include "game/gameobject_manager.h"
#include "game/game.h"

void kmain(multiboot_info_t* mBootInfo, u32 magic) {
    UNUSED(magic);

    idt_init();
    terminal_init();

    memory_manager_init(mBootInfo);
    graphics_init(mBootInfo);

    game_init();
    game_start();

    game_terminate();
    graphics_terminate();
}