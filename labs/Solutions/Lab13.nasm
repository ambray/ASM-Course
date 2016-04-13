bits 64

; LABS
global ex_strlen, ex_memcpy, ex_memset, ex_memcmp, ex_memchr, ex_strchr, ex_strcmp, ex_strcpy, ex_atoi,


; BONUS LABS
global ex_strstr, ex_isort, ex_qsort

ex_strlen:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    push rbp
    mov rbp, rsp
    mov rcx, -1
    xor rax, rax
    repne scasb
    not rcx
    dec rcx
    mov rax, rcx
    pop rbp
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ret

ex_memcpy:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    mov rcx, rdx
    rep movsb
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ret


ex_memset:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    mov rax, rsi
    mov rcx, rdx
    rep stosb
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ret

ex_memchr:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    mov rax, rsi
    mov rcx, rdx
    ;int3
    repne scasb
    dec rdi
    mov dl, [rdi]
    cmp al, dl
    jnz .not_found
    mov rax, rdi
    jmp .done
.not_found:
    xor rax, rax
.done:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ret

ex_memcmp:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    mov rcx, rdx
    repe cmpsb
    mov rax, rcx
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ret

ex_strchr:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    push rsi
    push rdi
    call ex_strlen ;rcx is now len
    pop rdi
    pop rsi
    mov rax, rsi
    repne scasb
    xor rdx, rdx
    dec rdi
    mov dl, byte [rdi]
    cmp dl, al
    jz .found
    xor rax, rax
    jmp .done
.found:
    mov rax, rdi
.done:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ret

ex_strcmp:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    push rdi
    push rsi
    call ex_strlen
    pop rdi
    push rcx
    push rdi ; old rsi
    call ex_strlen
    pop rsi
    pop rdx ; rdi -> strlen
    pop rdi
    cmp rdx, rcx
    jne .no_match
    repe cmpsb
    test rcx, rcx
    jz .equal
.no_match:
    mov rax, 1
    jmp .done
.equal:
    xor rax, rax
.done:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ret

ex_strcpy:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    push rsi
    push rdi
    mov rdi, rsi
    call ex_strlen
    pop rdi
    pop rsi
    rep movsb
    mov byte [rdi], 0x00
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ret


ex_atoi:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    push rbx
    push rdi
    call ex_strlen
    pop rdi
    mov rax, 1   ; step
    xor rbx, rbx ;
    xor r8, r8   ; accumulator
    mov r9, 10   ; static: 10
.continue:
    mov bl, [rdi + rcx - 1]
    sub bl, 0x30
    xchg rbx, rax   ; rax now contains the unpacked number
    test rax, rax
    jz .zero        ; skip 0's
    mul rbx         ; if not, multiply by the step
.zero:
    xchg rbx, rax   ; rax again contains our step, rdx the number
    add r8, rbx     ; add the number to accum
    mul r9          ; increase the step
    xor rbx, rbx    ; clear rdx
    loop .continue
    mov rax, r8
    pop rbx
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  |-- |      |--- |    |\     |    |   |   |-------
;  |   |      |    |    | \    |    |   |   |
;  |---- |    |    |    |  \   |    |   |   |_______
;  |     |    |    |    |   \  |    |   |           |
;  |     |    |    |    |    \ |    |   |           |
;  |____ |    |___ |    |     \|    |___|   ________|
;
;
;        |           |------ |   |------ |     |-------
;        |           |       |   |       |     |_______
;        |           |------ |   |-------- |           |
;        |           |       |   |         |           |
;        |_______    |       |   |_________|   ________|
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

ex_strstr:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  -BONUS-
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ret


ex_isort:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  insertion_sort.c is provided
;  to give an example implementation.
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ret


ex_qsort:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ret