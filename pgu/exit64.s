# x86_64 版本
# 64位系统的系统调用表的各个编号与32位的系统调用表的是不同的，可以查看ABI表了解详情

.section .data

.section .text

.globl _start

_start:

    movq $123, %rdi # 64位用rdi寄存器保存退出码
    movq $60, %rax  # 第60号系统调用是调用exit程序

    syscall         # 唤醒内核进行系统调用
