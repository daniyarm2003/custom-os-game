#include "isr.h"
#include "idt.h"

#include "../../drivers/terminal.h"

#define INITIALIZE_ISR(isrNum) idt_set_gate(isrNum, DPL_KERNEL_MODE, IDT_INTERRUPT_GATE_32, isr##isrNum)

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
}

void isr_handle(ISRRegisters* regs) {
    terminal_printf("Interrupt Number: %d\n", regs->interruptNum);
}