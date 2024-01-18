#ifndef _OS_PORTS_H
#define _OS_PORTS_H

#include "../include/basictypes.h"

#define PORT_VGA_CONTROL_REGISTER       0x3D4
#define PORT_VGA_DATA_REGISTER          0x3D5

u8 port_inb(u16 port);
void port_outb(u16 port, u8 data);

#endif