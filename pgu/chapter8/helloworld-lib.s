# PURPOSE: Write String to screen and exit
# use the library

# NOTICE: Using printf, the abi demands, that for 
# function with variable number of arguments 
# (printf is one of them), the number of used vector
# registers is passed in %al (which was not the case for x86).

.section .data
firststring:
    .ascii "I'm %s, from %s, %d years old.\n\0"
name:
    .ascii "Sun Chao\0"
area:
    .ascii "Wuchang District\0"
age:
    .quad 28

.section .text
    .globl _start

_start:

    # Write string to terminal
    movq $firststring, %rdi
    movq $name, %rsi
    movq $area, %rdx
    movq age, %rcx

    # the number of arguments
    mov $4, %al
    call printf

    # Exit this program
    movq $0, %rdi
    call exit

