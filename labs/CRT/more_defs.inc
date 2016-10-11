bits 64

struc Dirent
    .d_ino      resq    1   ; inode #
    .d_off      resq    1   ; Offset to next record
    .d_reclen   resw    1   ; length of this record
    .d_name     resb    1   ; Start of filename (NULL-terminated)
endstruc

struc Stat
    .st_dev         resq 1
    .st_ino         resq 1
    .st_nlink       resq 1
    .st_mode        resd 1
    .st_uid         resd 1
    .st_gid         resd 1
    .pad0           resb 4
    .st_rdev        resq 1
    .st_size        resq 1
    .st_blksize     resq 1
    .st_blocks      resq 1
    .st_atime       resq 1
    .st_atime_nsec  resq 1
    .st_mtime       resq 1
    .st_mtime_nsec  resq 1
    .st_ctime       resq 1
    .st_ctime_nsec  resq 1
endstruc

; Arguments for lseek (values for 3rd param - whence)
%define SEEK_SET        0   ; Seek from beginning of file
%define SEEK_CUR        1   ; Seek from current position
%define SEEK_END        2   ; Seek from the end of the file

%define sys_getdents    78
%define sys_execve      59
%define sys_stat        4
%define sys_lseek       8
%define sys_pause       34
