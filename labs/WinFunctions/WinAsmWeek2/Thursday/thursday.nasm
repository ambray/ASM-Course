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

;;;;;;;;;;;;;;;;;;;;;;;;;;
; END STUDENT CODE
;;;;;;;;;;;;;;;;;;;;;;;;;;