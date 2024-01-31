#ifndef _OS_ISR_H
#define _OS_ISR_H

#include "../../include/basictypes.h"

#define NUM_ISRS 32
#define NUM_IRQS 16

#define SLAVE_PIC_IRQ_START 8

#define CASCADE_IRQ_NUM 2
#define CASCADE_IRQ_MASK (1 << CASCADE_IRQ_NUM)

#define PIC_EOI_BYTE 0x20

#define ICW1_ICW4	0x01		/* Indicates that ICW4 will be present */
#define ICW1_SINGLE	0x02		/* Single (cascade) mode */
#define ICW1_INTERVAL4	0x04		/* Call address interval 4 (8) */
#define ICW1_LEVEL	0x08		/* Level triggered (edge) mode */
#define ICW1_INIT	0x10		/* Initialization - required! */
 
#define ICW4_8086	0x01		/* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO	0x02		/* Auto (normal) EOI */
#define ICW4_BUF_SLAVE	0x08		/* Buffered mode/slave */
#define ICW4_BUF_MASTER	0x0C		/* Buffered mode/master */
#define ICW4_SFNM	0x10		/* Special fully nested (not) */

typedef struct __attribute__((packed)) isr_regs_t {
    u32 ds;
    u32 edi, esi, ebp, esp, ebx, edx, ecx, eax;
    u32 interruptNum, errCode;
    u32 eip, cs, eflags, useresp, ss;
} ISRRegisters;

typedef void(*irq_handler_t)(ISRRegisters* regs);

void isr_init();

void isr_remap_pic();

void set_irq_handler(size_t irqNum, irq_handler_t handler);

void isr_handle(ISRRegisters* regs);
void irq_handle(ISRRegisters* regs);

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

#endif