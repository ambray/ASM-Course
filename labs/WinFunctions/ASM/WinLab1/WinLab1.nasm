bits 32

global _first_func@12, _second_func@8

section .text

;;;;;;;;;;;;;;;;;;;;;;;
;  Using SIMD instructions,
; add the values in firstVec
; (a pointer that points to a 
; 128 bit vector) with the values
; in secondVec, and store the
; results at thirdVec.
;
; void __stdcall first_func(int* firstVec, int* secondVec, int* thirdVec)
; BEGIN STUDENT CODE
;;;;;;;;;;;;;;;;;;;;;;;
_first_func@12:

;;;;;;;;;;;;;;;;;;;;;;;
; END STUDENT CODE
;;;;;;;;;;;;;;;;;;;;;;;


;;;;;;;;;;;;;;;;;;;;;;;
;  Using SIMD instructions,
; find the max of the two
; provided numbers, and
; return it.
;
; void __stdcall first_func(int first, int second)
; BEGIN STUDENT CODE
;;;;;;;;;;;;;;;;;;;;;;;
_second_func@8:

;;;;;;;;;;;;;;;;;;;;;;;
; END STUDENT CODE
;;;;;;;;;;;;;;;;;;;;;;;