bits 64

%include "defs.inc"
%include "more_defs.inc"


global _start, prints, lexit, mmap, munmap, lmalloc, free, check_free
global open, lseek, read, write, close, getdents, execve, strlen
extern main


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Entry Point               ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
_start:
  ret
