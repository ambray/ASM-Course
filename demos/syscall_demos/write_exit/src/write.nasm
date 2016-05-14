bits 64

; the write syscall number
%define sys_write  1
%define sys_exit   60
%define stdout     1 ; stdout

global write_stuff, exit_prog

get_len:
    xor rax, rax
    mov rcx, -1
    repne scasb
    not rcx
    dec rcx
    xchg rax, rcx
    ret

write_stuff:
    push rdi
    call get_len ; get our string length
    pop rsi      ; param 2: buffer to write
    mov rdx, rax ; param 3: length
    mov rax, sys_write
    mov rdi, stdout
    syscall
    ret

exit_prog:
    mov rax, sys_exit
    syscall
