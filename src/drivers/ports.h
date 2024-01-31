#ifndef _OS_PORTS_H
#define _OS_PORTS_H

#include "../include/basictypes.h"

#define PORT_PIC_MASTER_CONTROL         0x20
#define PORT_PIC_MASTER_DATA            0x21

#define PORT_KEYBOARD_CONTROLLER_DATA   0x60
#define PORT_KEYBOARD_CONRTOLLER_CMD    0x64

#define PORT_PIC_SLAVE_CONTROL          0xA0
#define PORT_PIC_SLAVE_DATA             0xA1

#define PORT_VGA_CONTROL_REGISTER       0x3D4
#define PORT_VGA_DATA_REGISTER          0x3D5

u8 port_inb(u16 port);
void port_outb(u16 port, u8 data);

#endif