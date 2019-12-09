.section .data

output_int:
    .ascii "int: %d\n\0"
output_ptr:
    .ascii "ptr: %p\n\0"

.section .bss
    # .lcomm defines a local uninitialized block of 
    # storage called a local common (LC)  section.
    .lcomm d, 8 # 定义长度为8字节的存储块

.section .text
.globl _start
_start:
    movq $output_int, %rdi
    movq d, %rsi # 把d的值放入寄存器
    mov $2, %al
    call printf

    movq $output_ptr, %rdi
    #movq $d, %rsi # 把d的地址放入寄存器
    movq $output_int, %rsi
    mov $2, %al
    call printf

    # Exit this program
    movq $0, %rdi
    call exit

