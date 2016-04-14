bits 64

global first_func, second_func, third_func

extern printf
mystr  db "Success!", 0xa, 0x00

first_func:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  The function printf has been
;  externed in (above). Call it,
;  passing mystr (also defined
;  above), as its only argument.
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ret

extern strlen

second_func:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   Your function will be called
;  with two arguments: a function
;  pointer (the first parameter),
;  and a string (the second). The
;  function pointer takes two
;  arguments: a string, and a length.
;  You will need to call strlen
;  (above), passing in the string,
;  and pass the results to the
;  function pointer (along with the
;  string). Return the string you get
;  back from the function. 
; 
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ret

third_func:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   Calculate the Nth fibonacci
;  number (where N is the value
;  passed to your method as the
;  only parameter).
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ret


