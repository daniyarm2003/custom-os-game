#include "isr.h"
#include "idt.h"

#include "../../drivers/terminal.h"
#include "../../drivers/keyboard.h"
#include "../../drivers/timer.h"

#include "../../drivers/ports.h"

#define INITIALIZE_ISR(isrNum) idt_set_gate(isrNum, DPL_KERNEL_MODE, IDT_INTERRUPT_GATE_32, isr##isrNum)
#define INITIALIZE_IRQ(irqNum) idt_set_gate(irqNum + NUM_ISRS, DPL_KERNEL_MODE, IDT_INTERRUPT_GATE_32, irq##irqNum)

static irq_handler_t irqHandlers[NUM_IRQS] = {};

void isr_init() {
    INITIALIZE_ISR(0);
    INITIALIZE_ISR(1);
    INITIALIZE_ISR(2);
    INITIALIZE_ISR(3);
    INITIALIZE_ISR(4);
    INITIALIZE_ISR(5);
    INITIALIZE_ISR(6);
    INITIALIZE_ISR(7);
    INITIALIZE_ISR(8);
    INITIALIZE_ISR(9);
    INITIALIZE_ISR(10);
    INITIALIZE_ISR(11);
    INITIALIZE_ISR(12);
    INITIALIZE_ISR(13);
    INITIALIZE_ISR(14);
    INITIALIZE_ISR(15);
    INITIALIZE_ISR(16);
    INITIALIZE_ISR(17);
    INITIALIZE_ISR(18);
    INITIALIZE_ISR(19);
    INITIALIZE_ISR(20);
    INITIALIZE_ISR(21);
    INITIALIZE_ISR(22);
    INITIALIZE_ISR(23);
    INITIALIZE_ISR(24);
    INITIALIZE_ISR(25);
    INITIALIZE_ISR(26);
    INITIALIZE_ISR(27);
    INITIALIZE_ISR(28);
    INITIALIZE_ISR(29);
    INITIALIZE_ISR(30);
    INITIALIZE_ISR(31);

    isr_remap_pic();

    INITIALIZE_IRQ(0);
    INITIALIZE_IRQ(1);
    INITIALIZE_IRQ(2);
    INITIALIZE_IRQ(3);
    INITIALIZE_IRQ(4);
    INITIALIZE_IRQ(5);
    INITIALIZE_IRQ(6);
    INITIALIZE_IRQ(7);
    INITIALIZE_IRQ(8);
    INITIALIZE_IRQ(9);
    INITIALIZE_IRQ(10);
    INITIALIZE_IRQ(11);
    INITIALIZE_IRQ(12);
    INITIALIZE_IRQ(13);
    INITIALIZE_IRQ(14);
    INITIALIZE_IRQ(15);

    isr_init_drivers();
}

void isr_remap_pic() {
    port_outb(PORT_PIC_MASTER_CONTROL, ICW1_INIT | ICW1_ICW4);
    port_outb(PORT_PIC_SLAVE_CONTROL, ICW1_INIT | ICW1_ICW4);

    port_outb(PORT_PIC_MASTER_DATA, NUM_ISRS);
    port_outb(PORT_PIC_SLAVE_DATA, NUM_ISRS + SLAVE_PIC_IRQ_START);

    port_outb(PORT_PIC_MASTER_DATA, CASCADE_IRQ_MASK);
    port_outb(PORT_PIC_SLAVE_DATA, CASCADE_IRQ_NUM);

    port_outb(PORT_PIC_MASTER_DATA, ICW4_8086);
    port_outb(PORT_PIC_SLAVE_DATA, ICW4_8086);

    // Unmask every IRQ
    port_outb(PORT_PIC_MASTER_DATA, 0x0);
    port_outb(PORT_PIC_SLAVE_DATA, 0x0);
}

void isr_init_drivers() {
    timer_init_handler();
    keyboard_init_handler();
}

void irq_set_handler(size_t irqNum, irq_handler_t handler) {
    irqHandlers[irqNum] = handler;
}

void isr_handle(ISRRegisters* regs) {
    terminal_printf("Interrupt Number: %d\n", regs->interruptNum);
}

void irq_handle(ISRRegisters* regs) {
    u32 irqNum = regs->errCode;

    if(irqNum >= SLAVE_PIC_IRQ_START) {
        port_outb(PORT_PIC_SLAVE_CONTROL, PIC_EOI_BYTE);
    }

    port_outb(PORT_PIC_MASTER_CONTROL, PIC_EOI_BYTE);

    if(irqHandlers[irqNum] != NULL) {
        irqHandlers[irqNum](regs);
    }
}