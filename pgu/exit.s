.section .data

.section .text

.globl _start

_start:
    movl $1, %eax   # system call number
    movl $-1, %ebx  # exit status code
    int $0x80
