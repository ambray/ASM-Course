bits 64

%define sys_exit    60
%define sys_clone   56

; Clone Flags
%define CLONE_VM      0x00000100 ; VM shared between procs.  
%define CLONE_FS      0x00000200 ; fs info shared  
%define CLONE_FILES   0x00000400 ; open files shared 
%define CLONE_SIGHAND 0x00000800 ; signal handlers shared.  
%define CLONE_THREAD  0x00010000 ; add to same thread group.  

global create_thread, exit_p

create_thread:
    push rdi ; Store our thread function

    ; Set clone flags
    mov rdi, CLONE_VM
    or rdi, CLONE_FS
    or rdi, CLONE_FILES
    or rdi, CLONE_SIGHAND
    or rdi, CLONE_THREAD

    lea rsi, [rsi + rdx - 8] ; get us 8 bytes shy of the end of our new stack
    ; Store exit at the very top of the stack
    mov rax, exit_p
    mov [rsi], rax
    ; Move down, and store our thread function here
    sub rsi, 8
    pop qword [rsi] 
    ; Perform the syscall
    mov rax, sys_clone
    syscall
    ; Parent returns to main(), child to
    ; the thread function, and then exit.
    ret

exit_p:
    mov rax, sys_exit
    xor rdi, rdi
    syscall
    
    
