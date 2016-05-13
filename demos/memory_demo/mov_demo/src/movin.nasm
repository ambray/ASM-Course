bits 64

global movin

movin:
    push rbp
    mov rbp, rsp
    mov rax, [rdi] ; copy the value to rax
    mov rcx, [rsi] ; get the value into rcx
    mov [rdi], rcx ; now we swap
    mov [rsi], rax ; again
    pop rbp
    ret
    
