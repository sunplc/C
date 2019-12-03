# PURPOSE: Write "helloworld" to screen, and exit

.include "linux.s"

.section .data
helloworld:
    .ascii "hello world\n"
helloworld_end:
    .equ helloworld_len, helloworld_end - helloworld

.section .text
.globl _start
_start:

    # Write string to terminal
    movq $SYS_WRITE, %rax
    movq $STDOUT, %rdi
    movq $helloworld, %rsi
    movq $helloworld_len, %rdx
    syscall

    # Exit this program
    movq $SYS_EXIT, %rax
    movq $0, %rdi
    syscall
