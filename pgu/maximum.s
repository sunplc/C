# PURPOSE: find the maximum number of the list

# %edi is index register
# %eax and %ebx is general purpose register, and %ebx holds
# exit status code, %eax holds system call number

.section .data
data_items:
    .long 123,12,4,123,155,23,78,234,17,10

.globl _start

.section .text
_start:
    movl $0, %edi

    start_loop:

    # compare %edi with the length of list
    cmpl $10, %edi
    je end_loop

    movl data_items(, %edi, 4), %eax

    cmpl $0, %edi
    jne check_index_is_zero
    movl %eax, %ebx
    check_index_is_zero:

    incl %edi

    cmpl %ebx, %eax
    jle start_loop

    movl %eax, %ebx
    jmp start_loop

    end_loop:

    movl $1, %eax
    int $0x80

