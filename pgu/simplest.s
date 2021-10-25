# 32位版，可以在64位上正确运行
# 最简单的汇编程序，通过中断调起第1号系统调用，
# 即退出程序，并设置程序退出码为123，
# 可以通过在终端执行 echo $? 来检查退出码

.section .text
.globl _start

_start:

    # 使用 int 退出程序 
    # 0x80 = 128 = Linux system call
    # movl $1, %eax
    # movl $123, %ebx
    # int $0x80     # int 0x80 on Linux always invokes the 32-bit ABI


    # 使用 syscall 退出程序
    movl $60, %eax  # _exit() is system call 60
    movl $123, %edi
    syscall
