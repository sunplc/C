# 计算一个整数的平方的函数

# square函数没用到stack, 所以没有操作 rbp 和 rsp，
# 仅在函数最后使用了 ret 指令，此时 ret 会弹出栈顶的值作为返回地址，
# 这个值正是 call 指令压入的地址。

.section .text

.globl _start

_start:

    movq $9, %rdi
    call square

    movq %rax, %rsi

    movq $7, %rdi
    call square_use_stack

    # 将两次函数调用返回值相加
    addq %rsi, %rax

    movq %rax, %rdi
    movq $60, %rax
    syscall

# square函数，没有使用栈
.type square, @function
square:

    imulq %rdi, %rdi
    movq %rdi, %rax

    ret

# square函数，使用栈
.type square_use_stack, @function
square_use_stack:
    pushq %rbp
    movq %rsp, %rbp

    subq $8, %rsp
    imulq %rdi, %rdi
    movq %rdi, -8(%rbp)
    movq -8(%rbp), %rax

    movq %rbp, %rsp
    popq %rbp

    ret

