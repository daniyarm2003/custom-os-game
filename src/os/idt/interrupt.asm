DATASEG         equ 0x10

section         .text

extern          isr_handle

interrupt_common:

pusha

push            ds

mov             eax, DATASEG

mov             ds, ax
mov             ss, ax
mov             es, ax
mov             fs, ax
mov             gs, ax

push            esp
call            isr_handle

add             esp, 4

pop             eax

mov             ds, ax
mov             ss, ax
mov             es, ax
mov             fs, ax
mov             gs, ax

popa
add             esp, 8

iret

%macro          isr_handler 1

global          isr%1
isr%1:

cli

push            0
push            %1

jmp             interrupt_common

%endmacro


%macro          isr_handler_err 1

global          isr%1
isr%1:

cli

push            %1

jmp             interrupt_common

%endmacro

isr_handler     0
isr_handler     1
isr_handler     2
isr_handler     3
isr_handler     4
isr_handler     5
isr_handler     6
isr_handler     7
isr_handler_err 8
isr_handler     9
isr_handler_err 10
isr_handler_err 11
isr_handler_err 12
isr_handler_err 13
isr_handler_err 14
isr_handler     15
isr_handler     16
isr_handler     17
isr_handler     18
isr_handler     19
isr_handler     20
isr_handler     21
isr_handler     22
isr_handler     23
isr_handler     24
isr_handler     25
isr_handler     26
isr_handler     27
isr_handler     28
isr_handler     29
isr_handler     30
isr_handler     31