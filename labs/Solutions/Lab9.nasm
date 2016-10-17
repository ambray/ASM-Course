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
    cmp rdi, 0          ; base case: value is 0
    jz .done_base   
    cmp rdi, 1          ; base case 2: value is 1
    jz .done_base 
    push rdi            ; Save the value we were called with
    dec rdi
    call _third_func    ; Call ourselves with n-1
    pop rdi
    push rax            ; Save the result of third_func(n-1)
    sub rdi, 2      
    call _third_func    ; Call ourselves with n-2
    pop rdi             ; restore the result of third_func(n-1)
    add rdi, rax        ; Add both together
    mov rax, rdi        ; Set to the return value
    jmp .done
.done_base:
    mov rax, rdi
.done:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ret


