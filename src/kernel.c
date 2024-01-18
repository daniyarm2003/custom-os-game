#include "lib/string.h"
#include "include/basicmacros.h"
#include "include/multiboot.h"
#include "drivers/terminal.h"

void kmain(multiboot_info_t* mBootInfo, u32 magic) {
    UNUSED(magic);

    terminal_init();
    terminal_printf("Hello World!\nName: %s\nNum: %d %% %c / %d", (const char*)mBootInfo->boot_loader_name, 65536, 'Y', -7);

    for(size_t i = 0; i <= 100; i++) {
        terminal_printf("Hello World %d!\n", i);
    }
}