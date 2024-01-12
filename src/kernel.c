#include "lib/string.h"
#include "include/basicmacros.h"
#include "include/multiboot.h"

void kmain(multiboot_info_t* mBootInfo, u32 magic) {
    UNUSED(magic);

    volatile short* vgaMem = (volatile short*)0xB8000;
    
    char testBuf[256];
    sprintf(testBuf, "Hello World %d %s!", mBootInfo->framebuffer_type, (char*)mBootInfo->boot_loader_name);

    for(size_t i = 0; testBuf[i]; i++) {
        vgaMem[i] = (0xF0 << 8) | testBuf[i];
    }
}