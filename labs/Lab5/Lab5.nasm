bits 64

extern _value, _value_outbuf, _second_value, _second_outbuf
global _first_func, _second_func, _third_func, _fourth_func, _fifth_func
global _sixth_func, _seventh_func

_first_func:
    push rbp
    mov rbp, rsp
    mov rax, 0xfeedbeef
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  Using the and instruction,
;  check to see if the 8th bit
;  is set in the value stored
;  in rax. Set rax equal to 1
;  if the bit is set, and 0 if
;  the bit is not set. Hint:
;  setting a register equal to
;  1 and left shifting may help.
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    pop rbp
    ret

_second_func:
    push rbp
    mov rbp, rsp
    mov rax, 0xdeadbeef
    mov rdx, 0xc0ffee
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  Check to see what bits are
;  set in both rdx and rax. Set
;  rax equal to the result.
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    pop rbp
    ret

_third_func:
    push rbp
    mov rbp, rsp
    mov rax, 0x1000
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  Without using the mov instruction,
;  set rax equal to 0.
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    pop rbp
    ret


_fourth_func:
    push rbp
    mov rbp, rsp
    mov rax, 0x08
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  Using only bit shifts,
;  multiply the value stored in
;  rax by 8.
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    pop rbp
    ret

_fifth_func:
    push rbp
    mov rbp, rsp
    mov rax, 32
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  Using only bit shift
;  instructions, divide the
;  value in rax by 16.
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    pop rbp
    ret

_sixth_func:
    push rbp
    mov rbp, rsp
    mov rax, _second_value
    mov rax, qword [rax]
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  The string Success! has been
;  been stored in rax, but is
;  slightly mangled ("ess!Succ").
;  Set it to
;  the correct order via byte
;  rotations (the result will
;  print out in console).
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    mov rcx, _second_outbuf
    mov rcx, [rcx]
    mov [rcx], rax
    pop rbp
    ret

_seventh_func:
    push rbp
    mov rbp, rsp
    mov rax, _value
    mov rax, qword [rax]
    mov rdx, 0xcc
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  An 8-byte message has been
;  XOR-encoded with the key 0xCC,
;  and stored in RAX. Using all
;  of the knowledge you've gained
;  so far, XOR each byte of RAX
;  with 0xCC. The resulting message
;  will print out in console.
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    mov rdi, _value_outbuf
    mov rdi, [rdi]
    mov [rdi], rax
    xor rax, rax
    pop rbp
    ret

