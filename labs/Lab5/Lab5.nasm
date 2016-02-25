bits 64

extern _value
global _first_func, _second_func

_first_func:
    push rbp
    mov rbp, rsp
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  For this task, you must allocate
;  8 bytes of space on the stack, and
;  store the value of rcx there.
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ret

_second_func
    push rbp
    mov rbp, rsp
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  For this task, you must allocate
;  manage your registers by saving them
;  to the stack as needed. Divide the
;  number stored where rcx points by 10,
;  and place the value back at that address.
;  Make sure all the register values are the
;  same at the end of the call!
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ret
