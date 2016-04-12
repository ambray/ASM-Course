bits 64

extern _first_value
global _first_func, _second_func, _third_func
global _out, _out2

section .data

_firstfloat dd 1.2345
_secondfloat dd 2.345
_out dd 0x0

_out2 dq 0x0
_tmp dq 0x0

section .text

_first_func:
    push rbp
    mov rbp, rsp
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;    This problem will require
;  you to load both _firstfloat
;  and _secondfloat (above) onto
;  the floating point stack, add
;  them together, and store the
;  result in _out.
; 
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    mov rax, _firstfloat
    fld dword [rax]
    mov rax, _secondfloat
    fld dword [rax]
    fadd
    mov rax, _out
    fstp dword [rax]
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    pop rbp
    ret

_second_func:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   This problem will require
;  you to add the contents of
;  _firstfloat to an integer
;  that is passed in as the
;  first (and only) argument
;  to your function. Store the
;  result at _out2.
; 
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    mov rax, _firstfloat
    fld dword [rax]
    mov rax, _tmp
    mov qword [rax], rdi
    fiadd dword [rax]
    mov rax, _out2
    fstp qword [rax]
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ret


