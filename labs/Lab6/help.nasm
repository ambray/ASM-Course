bits 64

global get_flags

get_flags:
    pushfq
    pop rax
    ret
