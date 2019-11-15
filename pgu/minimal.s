# 32bit version, ran on 64bit without problem

# PURPOSE: find the minimal number of the list

# %edi is index register
# %eax and %ebx is general purpose register, and %ebx holds
# exit status code, %eax holds system call number
# %ecx holds the end address of list
# %edx holds address of the current position of list

# INSTRUCTION:
# leal --Load effective address
# The lea instruction places the address specified by its 
# first operand into the register specified by its second 
# operand. Note, the contents of the memory location are 
# not loaded, only the effective address is computed and 
# placed into the register. This is useful for obtaining 
# a pointer into a memory region or to perform simple 
# arithmetic operations.

.section .data
data_items:
    .long 123,12,99,123,7,23,78,238,17,10

.globl _start

.section .text
_start:
    movl $0, %edi

    # %ecx holds the end address of the list
    leal data_items, %ecx
    addl $40, %ecx

    start_loop:

    # compare the end address of the list
    leal data_items(, %edi, 4), %edx
    cmpl %ecx, %edx
    jge end_loop

    movl data_items(, %edi, 4), %eax

    cmpl $0, %edi
    jne check_index_is_zero
    movl %eax, %ebx
    check_index_is_zero:

    incl %edi

    cmpl %ebx, %eax
    jge start_loop

    movl %eax, %ebx
    jmp start_loop

    end_loop:

    movl $1, %eax
    int $0x80

