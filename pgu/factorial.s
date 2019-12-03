# 64bit 版本
# 求一个数的阶乘，并将结果作为进程退出码返回

.section .data
resultstring:
    .ascii "the factorial of %d is %d.\n\0"

.section .text

.globl _start

_start:

    movq $6, %rdi # 保存第一个参数
    call factorial

    # 调用printf，参数一次存放在 %rdi, %rsi, %rdx
    movq %rdi, %rsi
    movq $resultstring, %rdi
    movq %rax, %rdx
    mov $3, %al # 保存参数个数
    call printf

    movq $60, %rax
    movq $0, %rdi
    syscall

