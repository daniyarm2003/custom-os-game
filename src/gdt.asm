section     .gdt

gdt_start:

gdt_null_desc:

dd          0x0, 0x0

gdt_code_desc:

dw          0xFFFF
db          0x0, 0x0, 0x0
db          0b10011010
db          0b11001111
db          0x0

gdt_data_desc:

dw          0xFFFF
db          0x0, 0x0, 0x0
db          0b10010010
db          0b11001111
db          0x0

gdt_end:

gdt_desc:

dw          gdt_end - gdt_start - 1
dd          gdt_start

CODESEG     equ gdt_code_desc - gdt_start
DATASEG     equ gdt_data_desc - gdt_start