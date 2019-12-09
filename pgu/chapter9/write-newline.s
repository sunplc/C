# PURPOSE: Write a newline character to STDOUT

# parameters:
#   %rdi - output file descritptor

.include "linux.s"

.globl write_newline
.type write_newline, @function

.section .data
newline:
.ascii "\n"

write_newline:
    
    movq $SYS_WRITE, %rax
    movq $newline, %rsi
    movq $1, %rdx
    syscall

    ret
