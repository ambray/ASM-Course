bits 32

global _sum_array@8, _find_largest

section .text


_sum_array@8:
;;;;;;;;;;;;;;;;;;;;;;;;;;
;
;	This method takes two parameters:
;
;	Param 1: A pointer to a buffer of integers (4 bytes/each).
;
;	Param 2: A number indicating the number of elements in the buffer.
;
;	You must:
;	1.) Walk through the buffer, and sum together all of the elements
;	2.) Return the result
;
;	int __stdcall sum_array(int* buffer, int size);
;
; BEGIN STUDENT CODE
;;;;;;;;;;;;;;;;;;;;;;;;;;
	push ebp
	mov ebp, esp
	push esi
	mov esi, [ebp + 8]
	mov ecx, [ebp + 12]
	xor eax, eax
	xor edx, edx
.continue:
	lodsd
	add edx, eax
	loop .continue

	xchg eax, edx
	pop esi
	pop ebp
	ret 8
;;;;;;;;;;;;;;;;;;;;;;;;;;
; END STUDENT CODE
;;;;;;;;;;;;;;;;;;;;;;;;;;


_find_largest:
;;;;;;;;;;;;;;;;;;;;;;;;;;
;
;	This function takes two
;	parameters:
;
;	Param 1: A pointer to a buffer of integers (4 bytes/each)
;
;	Param 2: A number indicating the number of elements in the
;	buffer.
;
;	Your task is to:
;	1.) Walk through the buffer, locating the largest element
;	2.) Return it as the result.	
;
;	int __cdecl find_largest(unsigned long* buffer, int size)
;
; BEGIN STUDENT CODE
;;;;;;;;;;;;;;;;;;;;;;;;;;
	push ebp
	mov ebp, esp
	push esi
	mov esi, [ebp + 8]
	mov ecx, [ebp + 12]
	xor eax, eax
	xor edx, edx
.continue:
	lodsd
	cmp eax, edx
	jg .larger
	jmp .skip
.larger:
	mov edx, eax
.skip:
	loop .continue
	xchg eax, edx
	pop esi
	pop ebp
	ret
;;;;;;;;;;;;;;;;;;;;;;;;;;
; END STUDENT CODE
;;;;;;;;;;;;;;;;;;;;;;;;;;