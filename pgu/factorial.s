# 64bit 版本
# 求一个数的阶乘，并将结果作为进程退出码返回

.section .text

.globl _start

_start:

    movq $4, %rdi # 保存第一个参数

    call factorial

    movq %rax, %rdi
    movq $60, %rax
    syscall

.type factorial, @function

factorial:
    pushq %rbp
    movq %rsp, %rbp

    cmp $1, %rdi    # 若参数等于1，则停止递归，返回1
    jg continue_mark
    movq $1, %rax
    jmp func_end

    continue_mark:

    subq $8, %rsp
    movq %rdi, -8(%rbp)
    #pushq %rdi             # 上面两句指令等同于本句指令

    decq %rdi
    call factorial
    popq %rdi
    imulq %rdi, %rax

    func_end:
    movq %rbp, %rsp
    popq %rbp
    ret

