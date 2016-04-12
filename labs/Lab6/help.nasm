bits 64

global _get_flags

_get_flags:
    pushfq
    pop rax
    ret
