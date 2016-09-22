bits 32

global _fibonacci@4, _walk_list_map@8


section .text


_fibonacci@4:
;;;;;;;;;;;;;;;;;;;;;;;;;;
;
;	This method takes a single parameter:
;	
;	Param 1: The fibonacci number to calculate (e.g., "5" would indicate
;	to calculate and return the 5th fibonacci number).
;
;	int __stdcall fibonacci(int n);	
;
; BEGIN STUDENT CODE
;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov eax, [esp + 4]
	test eax, eax
	jz .done
	cmp eax, 1
	jz .done
	push eax
	dec eax
	push eax
	call _fibonacci@4
	mov edx, eax
	pop eax
	sub eax, 2
	push edx
	push eax
	call _fibonacci@4
	pop edx
	add eax, edx
.done:
	ret 4
;;;;;;;;;;;;;;;;;;;;;;;;;;
; END STUDENT CODE
;;;;;;;;;;;;;;;;;;;;;;;;;;


struc Node
	.Next	resd  1
	.Data	resd  1
endstruc


_walk_list_map@8:
;;;;;;;;;;;;;;;;;;;;;;;;;;
;
;	This method takes two parameters:
;
;	Param 1: A pointer to the beginning of a linked list of nodes (structure
;	definition above)
;
;	Param 2: A function pointer
;
;	Your task:
;	1.) Walk the list of nodes
;	2.) For each node, call the function pointer provided
;	as parameter 2, giving it as input the Data from the node.
;
;	void __stdcall walk_list_map(Node* n, void(*)(size_t));
;
; BEGIN STUDENT CODE
;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov ecx, [esp + 4]
	mov edx, [esp + 8]
.continue:
	test ecx, ecx
	jz .done
	mov eax, [ecx + Node.Data]
	push ecx
	push eax
	call edx
	add esp, 4
	pop ecx
	mov ecx, [ecx]
	jmp .continue
.done:
	ret 8
;;;;;;;;;;;;;;;;;;;;;;;;;;
; END STUDENT CODE
;;;;;;;;;;;;;;;;;;;;;;;;;;