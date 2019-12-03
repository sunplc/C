
.globl factorial
.type factorial, @function
factorial:

factorial_begin:

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
    call factorial_begin
    popq %rdi
    imulq %rdi, %rax

func_end:

    movq %rbp, %rsp
    popq %rbp
    ret

