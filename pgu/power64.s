# 64位版本的函数调用，32位版本的暂时没有平台实验

# PURPOSE:
# calculate the result of n raised to power m.
# that is: rs = n^m

# NOTE:
# my machine is x86_bit architecture which doesn't has register %ebp
# and pushl instruction, so I use %rbp replace %ebp, use
# "push" instruction replace "pushl"


.section .text

.globl _start

_start:

    movq $2, %rdi # move first argument
    movq $3, %rsi # move second argument
    call power

    pushq %rax

    movq $2, %rdi # move first argument
    movq $5, %rsi # move second argument
    call power

    popq %rdi   # 从栈中取出第一次调用power的返回值
    addq %rax, %rdi # 退出码必须保存在rdi中

    movq $60, %rax # 系统调用编号必须保存在rax中
    syscall


# function power:
# parameter1 base number
# parameter2 power
.type power, @function
power:
    pushq %rbp # push old rbp onto stack
    movq %rsp, %rbp # let rbp holds current stack pointer address
    subq $8, %rsp # get room for out local storage
    

    movq %rdi, -8(%rbp)
    movq %rdi, %rax

    loop_for_power:
    cmpq $1, %rsi
    je end_loop_power

    movq -8(%rbp), %rax
    imulq %rdi, %rax
    movq %rax, -8(%rbp)

    decq %rsi
    jmp loop_for_power

    end_loop_power:
    movq -8(%rbp), %rax

    movq %rbp, %rsp
    popq %rbp

    ret

