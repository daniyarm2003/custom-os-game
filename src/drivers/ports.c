#include "ports.h"

u8 port_inb(u16 port) {
    u8 data;

    asm volatile (
        "inb %%dx, %%al"
        : "=a" (data)
        : "d" (port)
    );

    return data;
}

void port_outb(u16 port, u8 data) {
    asm volatile (
        "outb %%al, %%dx"
        : : "a" (data), "d" (port)
    );
}