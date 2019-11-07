.section .text
.globl _start

_start:

    movl $2, %ebx
    movl $1, %eax
    int $0x80
