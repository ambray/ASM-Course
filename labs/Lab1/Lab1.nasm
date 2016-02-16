bits 64

extern _value;
global _first_func, _second_func, _third_func, _fourth_func

_first_func:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  This is your first method for
;  the lab. First problem:
;  move the number 16 into
;  the register RAX.
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code.
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;
	ret

_second_func:
  mov rcx, 0x20
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; The second function in the lab
; involves moving a value from
; one register to another.
; Copy the contents of RCX into
; RAX.
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  ret


_third_func:
  mov rcx, _value
  mov rax, 0x10
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  The third function involves
;  moving a value from a register,
;  to a location in memory. RCX
;  currently contains a pointer
;  to some data. Copy the value
;  from RAX to the location
;  RCX points to.
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  ret


_fourth_func:
  mov rcx, _value
  xor rax, rax
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  For the fourth function, copy
;  the value stored in the
;  location RCX points to into
;  RAX.
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  ret
