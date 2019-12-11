# 从标准输入中读取一个字符串，并将其转换为整数

# EXERCISE:
# Write a program that reads a string of characters
# from STDIN and converts them to a number.

.include "number2integer.s"
.include "linux.s"

.section .data
    prompt:
    .ascii "\nThe integer you have typed in is: %d\n\0"

.section .bss
    .lcomm integer_buffer, 21

.section .text
    .globl _start
_start:

    movq $SYS_READ, %rax
    movq $STDIN, %rdi
    movq $integer_buffer, %rsi
    movq $20, %rdx
    syscall

    movq $integer_buffer, %rdi
    call number2integer

    movq $prompt, %rdi
    movq %rax, %rsi
    mov $2, %al
    call printf

    movq $SYS_EXIT, %rax
    movq $0, %rdi
    syscall
