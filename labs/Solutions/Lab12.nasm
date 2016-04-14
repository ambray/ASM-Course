bits 64

global first_func, second_func, third_func



first_func:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;    This problem will require
;  adding two vectors of numbers.
;  A pointer to two unaligned
;  vectors of 32-bit integers
;  have been passed as the first
;  two parameters to your function,
;  and a pointer to an empty
;  vector has been provided to store
;  the result.
; 
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    movups xmm0, [rdi]
    movups xmm1, [rsi]
    addps xmm0, xmm1
    movups [rdx], xmm0
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ret

second_func:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   This problem will require
;  you to compare the values
;  stored in the vector pointed
;  to by parameter 1 with the
;  values stored in the vector
;  pointed to by parameter 2.
;  Store the results of the
;  comparison in the vector
;  pointer to by parameter 3.
; 
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    movups xmm0, [rdi]
    movups xmm1, [rsi]
    cmpps xmm0, xmm1, 0
    movups [rdx], xmm0
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ret

third_func:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  Given two scalar values, passed
;  in as two parameters, find the max
;  of the two, and return it as your
;  result.
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    push rbp
    mov rbp, rsp
    sub rsp, 0x04
    xor rax, rax
    mov [rbp-4], edi
    movss xmm0, [rbp-4]
    mov [rbp-4], esi
    movss xmm1, [rbp-4]
    maxss xmm0, xmm1
    movss [rbp-4], xmm0
    mov eax, [rbp-4]
    add rsp, 0x04
    pop rbp
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ret