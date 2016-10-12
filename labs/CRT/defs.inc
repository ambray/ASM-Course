
; Page Protections
%define PROT_READ	0x1	 ; Page can be read.  
%define PROT_WRITE	0x2	 ; Page can be written.  
%define PROT_EXEC	0x4	 ; Page can be executed.  
%define PROT_NONE	0x0	 ; Page can not be accessed.  

%define stdout 1

; File mapping types
%define MAP_ANONYMOUS	0x20  ; Don't use a file.  
%define MAP_PRIVATE		0x02  ; Changes are private. 
%define MAP_SHARED	0x01  ; Share changes.  
%define MAP_GROWSDOWN	0x0100

; Flags to `msync'.  
%define MS_ASYNC	1  ; Sync memory asynchronously.  
%define MS_SYNC		4  ; Synchronous memory sync.  

; Open Options
%define O_RDONLY	   00
%define O_WRONLY	   01
%define O_RDWR		   02
%define O_CREAT	   0o100	; Create the file 
%define O_TRUNC	  0o1000	; Truncate (if exists) 
%define O_APPEND  0o2000 ; Append 

; Clone Flags
%define CLONE_VM      0x00000100 ; VM shared between procs.  
%define CLONE_FS      0x00000200 ; fs info shared  
%define CLONE_FILES   0x00000400 ; open files shared 
%define CLONE_SIGHAND 0x00000800 ; signal handlers shared.  
%define CLONE_THREAD  0x00010000 ; add to same thread group.  

; File Permissions... in Octal
%define S_IRWXU		0o0700 ; user  (file  owner)  has read, write and execute
%define S_IRUSR 	0o0400 ; user has read permission                         
%define S_IWUSR 	0o0200 ; user has write permission                        
%define S_IXUSR     	0o0100 ; user has execute permission                      
%define S_IRWXG     	0o0070 ; group has read, write and execute permission     
%define S_IRGRP		0o0040 ; group has read permission                        
%define S_IWGRP		0o0020 ; group has write permission                       
%define S_IXGRP		0o0010 ; group has execute permission                     
%define S_IRWXO		0o0007 ; others have read, write and execute permission   

; Wait Options
%define WSTOPPED	2 ; Stopped child process
%define WEXITED		4 ; exited child process
%define WCONTINUED	8 ; continued
; Check status, don't block
%define WNOWAIT		0x01000000


; Syscall numbers
%define sys_exit		60
%define sys_write   	1
%define sys_mmap		9
%define sys_munmap		11
%define sys_read		0
%define sys_open		2
%define sys_close		3
%define sys_unlink		87
%define sys_msync		26
%define sys_fsync		74
%define sys_clone		56
%define sys_wait4		61
