bits 64

extern _value
global _first_func

_first_func:
    mov rax, -1
    mov rcx, -1
    mov cl, 0x04
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  For this task, you must move
;  the first byte of RCX into
;  RAX, using zero extend.
;
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ret