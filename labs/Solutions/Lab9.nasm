bits 64

global _first_func, _second_func, _third_func

extern _printf
mystr  db "Success!", 0xa, 0x00

_first_func:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  The function printf has been
;  externed in (above). Call it,
;  passing mystr (also defined
;  above), as its only argument.
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    mov rdi, mystr
    sub rsp, 0x08
    call _printf
    add rsp, 0x08
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ret

extern _strlen

_second_func:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   Your function will be called
;  with two arguments: a function
;  pointer (the first parameter),
;  and a string (the second). The
;  function pointer takes two
;  arguments: a string, and a length.
;  You will need to call strlen
;  (above), passing in the string,
;  and pass the results to the
;  function pointer (along with the
;  string). Return the string you get
;  back from the function. 
; 
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    push rdi
    push rsi
    mov rdi, rsi
    sub rsp, 0x08
    call _strlen
    add rsp, 0x08
    pop rdi
    pop rcx
    mov rsi, rax
    sub rsp, 0x18
    call rcx
    add rsp, 0x18
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ret

_third_func:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   Calculate the Nth fibonacci
;  number (where N is the value
;  passed to your method as the
;  only parameter).
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    cmp rdi, 0
    jz .done_zero
    cmp rdi, 1
    jz .done_one 
    push rdi
    dec rdi
    call _third_func
    pop rdi
    push rax
    sub rdi, 2
    call _third_func
    pop rdi
    add rdi, rax
    mov rax, rdi
    jmp .done
.done_zero:
    xor rax, rax
.done_one:
    mov rax, rdi
.done:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ret


