# 32位版本，可以在 x86_64 上正常执行

.section .data

.section .text

.globl _start

_start:
    movl $1, %eax   # 第一号系统调用是退出程序
    movl $123, %ebx  # 设置进程退出码

    # 中断指令，中断向量表中第128号中断是系统调用 
    int $0x80
