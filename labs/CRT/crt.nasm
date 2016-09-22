bits 64

%include "defs.inc"
%include "more_defs.inc"

%define PROT_READ       0x1      ; Page can be read.
%define PROT_WRITE      0x2      ; Page can be written.
%define PROT_EXEC       0x4      ; Page can be executed.
%define PROT_NONE       0x0      ; Page can not be accessed.
%define MAP_ANONYMOUS   0x20     ; Don't use a file. (flag)
%define MAP_PRIVATE     0x02     ; Changes are private.  (flag)
%define MAP_SHARED      0x01  	 ; Share changes. (flag)

myString db "This prints something to the screen.", 0xA, 0x00    ; 37 characters to print, including the newline


global _start, prints, lexit, mmap, munmap, lmalloc, free, check_free
global open, lseek, read, write, close, getdents, execve, strlen
extern main


struc Node
  .next resq  1
  .data resq  1
endstruc


struc List
   .head resq 1
endstruc



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;	    _start	     ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
_start:
  call main
  call lexit
ret		; need a ret here?


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;           prints          ;;
;;     (print to screen)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
prints:
    mov rax, 1
    mov rdi, 1			; reserved descriptor for stdout
    mov rsi, myString
    mov rdx, 37 
    syscall
ret


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;           lexit	     ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
lexit:
    mov rax, 60
    xor rdi, rdi
    syscall 
ret


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;           mmap	     ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
mmap:
   mov rax, 9			; rax needs syscall 9, the code for sys_mmap
   mov rsi, rdi  		; rsi needs the length, so we put the length argument there
   mov rdx, PROT_READ
   or rdx, PROT_WRITE
   mov r10, MAP_ANONYMOUS
   or r10, MAP_PRIVATE
   mov r8, 0
   mov r9, 0

   syscall
ret


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;           munmap	     ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; input parameter:
;   rdi - contains the address of the target memory chunk to free up, starting with the size qword
munmap:
   mov rax, 11			; rax needs 11, the syscall code for sys_munmap
;   mov rsi, [rdi]  		; rsi needs the length, so we put the length argument there
   mov rsi, rdi   
   syscall
ret


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;           lmalloc          ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; input parameter:
;   rdi - number of bytes to allocate
lmalloc:
   add rdi, 8			; add one more byte to what the user requested, for our size qword 
   call mmap

ret



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;           free            ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; input parameters:
;   rdi - contains a pointer to the memory chunk to free up

free:
   sub rdi, 8			; move the pointer back to unmap the size qword too

   call munmap 

ret


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;           check_free	     ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
check_free:

; linked list code goes here

ret


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;                       open                              ;;
;; open - open a file					   ;;
;; int open(const char *pathname, int flags, mode_t mode); ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
open:
    mov rax, 2			; prescribed by syscall table
    syscall
ret


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;                       lseek				 ;;
;; lseek - reposition read/write file offset		 ;; 
;; off_t lseek(int fd, off_t offset, int whence);	 ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
lseek:
    mov rax, 8			; prescribed by slide 15 
    syscall
	int3
ret


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;                       read				 ;;
;; read - read from a file descriptor       		 ;; 
;; ssize_t read(int fd, void *buf, size_t count);	 ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
read:
    mov rax, 0			; prescribed by syscall table
    syscall
ret


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;           write	                                 ;;
;; write - write to a file descriptor                    ;;
;; ssize_t write(int fd, const void *buf, size_t count); ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
write:
    mov rax, 1			; prescribed by syscall table
    syscall
ret



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;           		close				 ;;
;; close - close a file descriptor                       ;;
;; int close(int fd);					 ;; 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
close:
    mov rax, 3			; prescribed by syscall table
    syscall
ret



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;           		getdents			 ;;
;; getdents - get directory entries                      ;;
;; int getdents(unsigned int fd, struct linux_dirent *dirp, unsigned int count);
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
getdents:
    mov rax, 78			; prescribed by slide 19
    syscall
ret



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;           		execve				 ;;
;;  execve - execute program                             ;;
;;  int execve(const char *filename, char *const argv[],  char *const envp[]);
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
execve:
    mov rax, 59			; prescribed by slide 20
    syscall
ret


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; 		strlen 
;
; size_t strlen(char*);  
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
strlen:
   xor rax, rax                    ; zero out rax because lods puts a value here
   xor ebx, ebx                    ; use ebx as our strlen counter
   mov rsi, rdi                    ; because lods needs the pointer in rsi
        
.continue:
   lodsb                        ; grabs a byte from rsi buffer, loads it into al, increments pointer
   test al, al                  ; test for 0 "nul-terminator"
   jnz .adder                   ; if not nul, go increment the counter
   jz .end                      ; if nul, go to the end
.adder:
   inc ebx                      ; increment our counter
   jmp .continue
.end:
   mov eax, ebx                 ; move the counter into rax, the conventional return register
ret


