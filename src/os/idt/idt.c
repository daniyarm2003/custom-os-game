#include "idt.h"
#include "isr.h"

#include "../include/segments.h"

static IDTGateDescriptor idt[IDT_SIZE] = {};
static IDTDescriptor idtDesc;

void idt_init() {
    idtDesc.idtSize = (u16)(sizeof(idt) - 1);
    idtDesc.idtOffset = (u32)&idt;

    isr_init();

    asm volatile (
        "lidtl (%0)\n"
        "sti"
        : : "r" (&idtDesc)
    );
}

void idt_set_gate(size_t gateIndex, u8 dpl, IDTGateType gateType, isr_func_t isrHandler) {
    uintptr_t offset = (uintptr_t)isrHandler;

    idt[gateIndex].offsetLow = (u16)(offset & 0xFFFF);
    idt[gateIndex].offsetHigh = (u16)((offset >> 16) & 0xFFFF);

    idt[gateIndex].segmentSelector = GDT_CODE_SEGMENT;

    idt[gateIndex].typeAttribs = (1 << 7) | ((dpl & 0b11) << 5) | ((u8)gateType & 0x0F);
}