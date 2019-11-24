# x86_64 version of the book's exercises

.section .data
list1:
.quad 23,211,54,234,66, 0, 43

list2:
.quad 24,12,3,33,7,9

list3:
.quad 6,8,-7,5,9,10,12,70,34

.section .text

.globl _start
_start:

    # list1 是一个很特殊的符号, 保存着内存地址,
    # 直接使用mov操作时，会获得其首个元素的值,
    # 而使用lea操作时，会获得其地址，所以list1
    # 类似是一个寄存器

    leaq list1, %rdi
    # movq $list1, %rdi # 和上一行是等价的

    movq $7, %rsi
    call maximum

    leaq list2, %rdi
    movq $6, %rsi
    call maximum

    leaq list3, %rdi
    movq $9, %rsi
    call maximum

    movq %rax, %rdi
    movq $60, %rax
    syscall

# 求取整数列表的最大数
# 两个参数：
# %rdi 指向整数列表的指针
# %rsi 列表长度
.type maximum, @function
maximum:
    pushq %rbp
    movq %rsp, %rbp

    movq $0, %rax
    movq (%rdi), %rbx

    start_loop:

    cmpq %rsi, %rax
    jge end_loop

    movq (%rdi, %rax, 8), %rcx
    incq %rax

    cmpq %rcx, %rbx
    jge start_loop

    movq %rcx, %rbx
    jmp start_loop

    end_loop:

    movq %rbx, %rax

    movq %rbp, %rsp
    popq %rbp

    ret
