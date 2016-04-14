bits 64

extern first_value
global first_func, second_func, third_func
global out1, out2

section .data

firstfloat dd 1.2345

secondfloat dd 2.345

out1 dd 0x00


out2 dq 0x00

tmp dq 0x00

section .text

first_func:
    push rbp
    mov rbp, rsp
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;    This problem will require
;  you to load both firstfloat
;  and secondfloat (above) onto
;  the floating point stack, add
;  them together, and store the
;  result in out1.
; 
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    pop rbp
    ret

second_func:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   This problem will require
;  you to add the contents of
;  _firstfloat to an integer
;  that is passed in as the
;  first (and only) argument
;  to your function. Store the
;  result at out2.
; 
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ret


