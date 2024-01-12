MBALIGN         equ 1 << 0
MEMINFO         equ 1 << 1
VIDMODE         equ 1 << 2

MBFLAGS         equ MEMINFO | MBALIGN

MAGIC           equ 0x1BADB002
CHECKSUM        equ -(MBFLAGS + MAGIC)

section         .multiboot

align           4

dd              MAGIC
dd              MBFLAGS
dd              CHECKSUM

dd              0, 0, 0, 0, 0

dd              0
dd              800
dd              600
dd              32

section         .bss

align           0x10

stack_bottom:
resb            0x4000
stack_top:

section         .text

global          _start
_start:

mov             esp, stack_top

push            eax
push            ebx

extern          kmain
call            kmain

add             esp, 8

cli

hang:

hlt
jmp             hang