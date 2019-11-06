# program purpose: find the maximum number of the list
# %edi is index register
# %eax and %ebx is general purpose register, and %ebx holds
# exit status code, %eax holds system call number

.section .data
data_items:
    .long 23,12,2,123,155,23,78,238,1,0

.globl _start

.section .text
_start:
    movl $0, %edi
    movl (data_items), %eax
    movl %eax, %ebx

    start_loop:
    cmpl $0, %eax
    je end_loop

    incl %edi
    movl data_items(, %edi, 4), %eax

    cmpl %ebx, %eax
    jle start_loop

    movl %eax, %ebx
    jmp start_loop

    end_loop:

    movl $1, %eax
    int $0x80
