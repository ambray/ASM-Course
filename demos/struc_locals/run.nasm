bits 64

extern my_function
extern exit

global run_me

struc Locals
	.First	resd	1
	.Second resq	1	
	.Third 	resd	1
endstruc

run_me:
    push rbp
    mov rbp, rsp
    sub rsp, 0x10
    mov [rbp - 4 - Locals.First], edi
    mov [rbp - 8 - Locals.Second], rsi
    mov [rbp - 4 - Locals.Third], edx
    xor rax, rax
    mov eax, [rbp - 4 - Locals.First]
   	add rsp, 0x10
   	pop rbp
    ret
