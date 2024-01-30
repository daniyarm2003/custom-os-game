#ifndef _OS_IDT_H
#define _OS_IDT_H

#include "../../include/basictypes.h"

#define IDT_SIZE 256

#define DPL_KERNEL_MODE 0b00
#define DPL_USER_MODE   0b11

typedef enum {
    IDT_TASK_GATE = 0x5,
    IDT_INTERRUPT_GATE_16 = 0x6,
    IDT_TRAP_GATE_16 = 0x7,
    IDT_INTERRUPT_GATE_32 = 0xE,
    IDT_TRAP_GATE_32 = 0xF
} IDTGateType;

typedef struct __attribute__((packed)) idt_gate_desc_t {
    u16 offsetLow;
    u16 segmentSelector;
    u8 unused;
    u8 typeAttribs;
    u16 offsetHigh;
} IDTGateDescriptor;

typedef struct __attribute__((packed)) idt_desc_t {
    u16 idtSize;
    u32 idtOffset;
} IDTDescriptor;

typedef void(*isr_func_t)();

void idt_init();
void idt_set_gate(size_t gateIndex, u8 dpl, IDTGateType gateType, isr_func_t isrHandler);

#endif