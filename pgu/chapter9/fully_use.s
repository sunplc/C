# EXERCISE:
# Modify the memory manager so that if the 
# requested size of memory is smaller than
# the region chosen, it will break up the region
# into multiple parts. Be sure to take into
# account the size of the new header record when
# you do this.

# Use command 'strace ./fully_use' to check if 
# allocator fully used the heap memory chunk


# include allocator define file
.include "alloc.s"

.section .data
    msg:
    .ascii "this is a test message!\n\0"

.section .bss
    .lcomm ptr, 8

.section .text
# Main program
.globl _start
_start:

    movq $1200, %rdi
    call allocate
    movq %rax, ptr

    movq ptr, %rdi
    movq $msg, %rsi
    call strcpy

    # %rdi holds ptr at this moment
    movq ptr, %rdi
    mov $1, %al
    call printf
    
    movq ptr, %rdi
    call deallocate

    movq $30, %rdi
    call allocate

    movq $10, %rdi
    call allocate

    movq $60, %rax
    movq $0, %rdi
    syscall

