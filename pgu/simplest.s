# 最简单的汇编程序，通过中断调起第1号系统调用，
# 即退出程序，并设置程序退出码为123，
# 可以通过在终端执行 echo $? 来检查退出码

.section .text
.globl _start

_start:

    movl $123, %ebx
    movl $1, %eax
    int $0x80
