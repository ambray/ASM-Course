bits 64

extern value
global first_func, second_func

first_func:
    push rbp
    mov rbp, rsp
    mov rcx, 0x10
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
    pop rax
    pop rbp
    ret

second_func
    push rbp
    mov rbp, rsp
    mov rcx, value
    mov rax, 1
    mov rdx, 2
    mov rsi, 3
    mov rdi, 4
    mov r8, 5
    mov r9, 6
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  For this task, you must allocate
;  space to 
;  manage your registers and save them
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
    cmp rax, 1
    jnz .fail
    cmp rdx, 2
    jnz .fail
    cmp rsi, 3
    jnz .fail
    cmp rdi, 4
    jnz .fail
    cmp r8, 5
    jnz .fail
    cmp r9, 6
    jnz .fail
    jmp .end
.fail:
    mov rax, -1
.end:
    pop rbp
    ret
