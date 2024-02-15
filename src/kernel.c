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

    terminal_printf("Hello World!\nName: %s\nNum: %d %% %c / %d", (const char*)mBootInfo->boot_loader_name, 65536, 'Y', -7);

    for(size_t i = 0; i <= 10; i++) {
        terminal_printf("Hello World %d!\n", i);
    }

    asm volatile (
        "int $3"
    );

    terminal_printf("START: %d, END: %d\n", &kernel_start, &kernel_end);

    while(true) {
        sleep_for_timer_ticks(1000);
    }
}