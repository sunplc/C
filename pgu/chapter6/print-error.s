.include "linux.s"

# 输出一条错误信息到标准错误输出
# Parameters:
# $rax - pointer to the error message
# %rdi - length of the error message

.globl print_error
.type print_error, @function
print_error:

    movq %rax, %rsi
    movq %rdi, %rdx
    movq $SYS_WRITE, %rax
    movq $STDERR, %rdi # file to use
    syscall

    ret

