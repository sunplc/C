.section .text

.globl _start
_start:

    movq $5, %rax
    movq %rax, %rbx

    start_loop:
    decq %rax
    cmpq $0, %rax
    jle end_loop
    imulq %rax, %rbx
    jmp start_loop
    end_loop:

    movq %rbx, %rdi
    movq $60, %rax
    syscall
