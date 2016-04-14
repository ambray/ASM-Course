bits 32

global _first_func@8, _second_func@8, _third_func, _fourth_func@12

section .text


;;;;;;;;;;;;;;;;;;;;;;;
;  Standard Call
; Using the following
; function definition,
; add the first parameter
; to the second, and return
; the result (via eax).
;
;
; int __stdcall first_func(int v1, int v2)
; BEGIN STUDENT CODE
;;;;;;;;;;;;;;;;;;;;;;;
_first_func@8:
	push ebp
	mov ebp, esp

	mov eax, [ebp + 8]
	mov ecx, [ebp + 0x0c]
	add eax, ecx

	pop ebp
	ret 0x08
;;;;;;;;;;;;;;;;;;;;;;;
; END STUDENT CODE
;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;
;  Standard Call
; Using the following
; function definition,
; subtract the second parameter
; from the first, and return
; the result (via eax).
;
; int __stdcall second_func(int v1, int v2)
; BEGIN STUDENT CODE
;;;;;;;;;;;;;;;;;;;;;;;
_second_func@8:
	push ebp
	mov ebp, esp

	mov eax, [ebp + 8]
	mov ecx, [ebp + 0x0c]
	sub eax, ecx

	pop ebp
	ret 0x08
;;;;;;;;;;;;;;;;;;;;;;;
; END STUDENT CODE
;;;;;;;;;;;;;;;;;;;;;;;


;;;;;;;;;;;;;;;;;;;;;;;
;  cdecl
; Using the following
; function definition,
; given a NULL-terminated
; string, and a max value
; for length, find and return
; the string's length.
;
; size_t __cdecl third_func(char* string, size_t maxlen)
; BEGIN STUDENT CODE
;;;;;;;;;;;;;;;;;;;;;;;
_third_func:
	push ebp
	mov ebp, esp
	mov edi, [ebp + 8]
	mov ecx, [ebp + 0x0c]
	xor eax, eax
	repne scasb
	mov edx, [ebp + 8]
	sub edi, edx
	mov eax, edi
	pop ebp
	ret
;;;;;;;;;;;;;;;;;;;;;;;
; END STUDENT CODE
;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;
;  Standard Call
; Give the following function
; definition, which takes:
; 1.) a pointer to a set of
; obfuscated bytes
; 2.) a pointer to a destination
; array
; 3.) a size to operate on
; XOR each obfuscated byte
; by the constant value
; 0x5f, and store the result
; in the destination.
;
; void __stdcall fourth_func(unsigned char* input, char* output, size_t len)
; BEGIN STUDENT CODE
;;;;;;;;;;;;;;;;;;;;;;;
_fourth_func@12:
	push ebp
	mov ebp, esp
	mov esi, [ebp + 8]
	mov edi, [ebp + 0x0c]
	mov ecx, [ebp + 0x10]
.continue:
	lodsb
	xor al, 0x5f
	stosb
	loop .continue
	pop ebp
	ret 0x0c
;;;;;;;;;;;;;;;;;;;;;;;
; END STUDENT CODE
;;;;;;;;;;;;;;;;;;;;;;;