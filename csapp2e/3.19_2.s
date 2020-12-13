
.section .data
resultstring:
    .ascii "result: %d \n\0"

.globl _start

_start:

    movq $1, %rax
    movq $2, %rdx

    # maximum of 64 bits signed long int
    movq $1, %rbx
    shlq $63, %rbx
    subq $1, %rbx

loop_start:
    movq %rax, %rcx
    imulq %rdx, %rax

    # 大于 rbx，代表已溢出
    cmpq %rbx, %rax
    jg loop_end

    # 乘积的结果比本身小，代表已溢出
    cmpq %rcx, %rax
    jle loop_end


    addq $1, %rdx

    jmp loop_start

loop_end:

    # %edx 减一得到上一步未溢出时的最大值
    subl $1, %edx

    # Use system call to exit process,
    # the exit code should set in register %edi
    movl %edx, %edi
    movl $60, %eax
    syscall

