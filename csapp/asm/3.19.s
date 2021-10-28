
.section .data
resultstring:
    .ascii "result: %d \n\0"

.globl _start

_start:

    movl $1, %eax
    movl $2, %edx

    # maximum of 32 bits signed int
    movl $1, %ebx
    shll $31, %ebx
    subl $1, %ebx

loop_start:
    movl %eax, %ecx
    imull %edx, %eax

    # 大于 ex ，代表已溢出
    cmpl %ebx, %eax
    jg loop_end

    # 乘积的结果比本身小，代表已溢出
    cmpl %ecx, %eax
    jle loop_end


    addl $1, %edx

    jmp loop_start

loop_end:

    # %edx 减一得到上一步未溢出时的最大值
    subl $1, %edx

    # Use system call to exit process,
    # the exit code should set in register %edi
    movl %edx, %edi
    movl $60, %eax
    syscall

