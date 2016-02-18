bits 64

global _first_func, _second_func, _third_func, _fourth_func, _fifth_func


_first_func:
    mov rax, 10
;;;;;;;;;;;;;;;;;;;;;;;;;;
;  For this test, you will
;  need to add 10 to the
;  value stored in rax.
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;
    ret

_second_func:
    mov rax, 30
;;;;;;;;;;;;;;;;;;;;;;;;;;
;  For this test you will
;  need to subtract 20
;  from the value in rax.
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;
    ret



_third_func:
    mov rax, 10
;;;;;;;;;;;;;;;;;;;;;;;;;;
;  For this lab, you will
;  need to multiply rax by
;  10.
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;
    ret

_fourth_func:
    mov rax, 10
;;;;;;;;;;;;;;;;;;;;;;;;;;
;  For this lab, you will
;  need to divide by 2,
;  and return the dividend.
;  hint: make sure you clear
;  the high bits!
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;
    ret

_fifth_func:
    mov rax, 7
;;;;;;;;;;;;;;;;;;;;;;;;;;
;  For this lab, you will
;  be required to divide
;  by 2, and move the
;  remainder into rax.
;  hint: make sure you
;  clear the high bits!
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;
    ret