# 将一个正整数转换成十进制的字符串表示

.include "linux.s"
.section .data

# This is where decimal string will be stored, length: 22
    tmp_buffer:
    .ascii "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    
.section .text
    .globl _start
_start:
    movq %rsp, %rbp
    
    movq $5294,  %rdi #Number to convert
    movq $tmp_buffer, %rsi #Storage for the result
    movq $3, %rdx # base of numbers [0 -> 10, 1 -> 2, 2 -> 8]
    call integer2string
    
    #Get the character count for our system call
    movq $tmp_buffer, %rdi
    call count_chars
    
    
    #The count goes in %edx for SYS_WRITE
    movq %rax, %rdx
    #Make the system call
    movq $SYS_WRITE, %rax
    movq $STDOUT, %rdi
    movq $tmp_buffer, %rsi
    syscall
    
    #Write a carriage return
    movq $STDOUT, %rdi
    call write_newline
    
    #Exit
    movq $SYS_EXIT, %rax
    movq $0, %rdi
    syscall

