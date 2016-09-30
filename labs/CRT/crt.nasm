bits 64

%include "defs.inc"
%include "more_defs.inc"


global _start ; Expose _start for linking
extern main   ; Implemented in main.c


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Entry Point               ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
_start:
  ret
