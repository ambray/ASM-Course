bits 64

extern _buf
global _first_func

_first_func:
    push rbp
    mov rbp, rsp
    xor rax, rax
    mov al, 0x41
    mov rcx, 0x20
    push rdi
    lea rdi, [rbp + 8]
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  For this task, you must allocate
;  32 bytes of space on the stack.
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    sub rsp, 0x20
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    rep stosb
    push rsi
    mov rsi, rdi
    mov rdi, _buf
    mov rcx, 0x20
    rep movsb
    pop rsi
    add rsp, 0x20
    pop rdi
    pop rbp
    ret
