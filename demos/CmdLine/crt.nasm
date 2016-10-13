bits 64

%include "defs.inc"
%include "more_defs.inc"


global _start ; Expose _start for linking
extern main   ; Implemented in main.c


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Entry Point               ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
_start:
  mov rcx, [rsp]
  mov rsi, [rsp + 8]
  mov rdi, [rsp + 16]
  mov r8, [rsp + 24]
  int3
  ret
