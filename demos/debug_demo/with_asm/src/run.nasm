bits 64

global run_me

run_me:
    int3
    mov rcx, -1
    xor rax, rax
    repne scasb
    not rcx
    dec rcx
    xchg rcx, rax
    ret
