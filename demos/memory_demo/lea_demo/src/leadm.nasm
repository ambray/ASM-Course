bits 64

global calc_address

calc_address:
    lea rax, [rdi+0x10]
    ret
