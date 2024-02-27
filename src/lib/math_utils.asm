section         .text

%macro          func_wrapper 1

global          __%1_util
__%1_util:

push            ebp
mov             ebp, esp

fld             dword [ebp + 0x8]
%1

pop             ebp
ret

%endmacro

func_wrapper    fsqrt
func_wrapper    fsin
func_wrapper    fcos