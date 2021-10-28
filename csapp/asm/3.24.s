
.globl _start

_start:

    movl $0, %eax # sum
    movl $0, %ebx # i

loop_start:
    cmpl $10, %ebx
    jge loop_end

    # check whether i is even number
    movl %ebx, %ecx
    andl $1, %ecx
    cmpl $0, %ecx
    jg continue

    addl %ebx, %eax # add i to sum

continue:

    addl $1, %ebx
    jmp loop_start

loop_end:

    # Use system call to exit process,
    # the exit code should set in register %edi
    movl %eax, %edi
    movl $60, %eax
    syscall

