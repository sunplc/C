# x86_64 version of the book's exercise

# EXERCISE: Write a program that will create a file called
# "heynow.txt" and write the words "Hey diddle diddle!" 
# into it.

.section .data 
    content:
    .ascii "Hey diddle diddle!\0"
    filename:
    .ascii "heynow.txt\0"

.section .text
    .equ SYS_OPEN, 2
    .equ SYS_WRITE, 1
    .equ SYS_READ, 0
    .equ SYS_CLOSE, 3
    .equ SYS_EXIT, 60

    .equ O_CREAT_WRONLY_TRUNC, 03101

.globl _start
_start:
    movq %rsp, %rbp

    movq $SYS_OPEN, %rax
    movq $filename, %rdi
    movq $O_CREAT_WRONLY_TRUNC, %rsi
    movq $0666, %rdx
    syscall

    subq $8, %rsp
    movq %rax, -8(%rbp)

    movq $SYS_WRITE, %rax
    movq -8(%rbp), %rdi
    movq $content, %rsi
    movq $18, %rdx
    syscall

    movq $SYS_CLOSE, %rax
    movq -8(%rbp), %rdi
    syscall
    
    movq $123, %rdi # 64位用rdi寄存器保存退出码
    movq $SYS_EXIT, %rax  # 第60号系统调用是调用exit程序
    syscall         # 唤醒内核进行系统调用

