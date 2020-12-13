
.globl _start

_start:

    movl $14, %eax
    movl $9, %ebx

    cmpl %eax, %ebx

    jg L1

    movl $1, %edi
    movq $60, %rax
    syscall

L1:
    movl $0, %edi
    movq $60, %rax
    syscall

