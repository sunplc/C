# x86_64 version of the book's example

# NOTE:
# 1) use syscall instruction, instead of int instruction
# 2) use eightbyte register and instruction ,
#       instead of fourbyte register
# 3) use register to hold function arguments, instead of stack

# PURPOSE: This program converts an input file
# to an output file with all letters
# converted to uppercase.
#
# PROCESSING: 1) Open the input file
#   2) Open the output file
#   4) While we’re not at the end of the input file
#       a) read part of file into our memory buffer
#       b) go through each byte of memory
#       if the byte is a lower-case letter,
#       convert it to uppercase
#       c) write the memory buffer to output file

.section .data

#######CONSTANTS########
# system call numbers
    .equ SYS_OPEN, 2
    .equ SYS_WRITE, 1
    .equ SYS_READ, 0
    .equ SYS_CLOSE, 3
    .equ SYS_EXIT, 60

# options for open (look at
# /usr/include/asm/fcntl.h for
# various values. You can combine them
# by adding them or ORing them)
# This is discussed at greater length
# in "Counting Like a Computer"
    .equ O_RDONLY, 0
    .equ O_CREAT_WRONLY_TRUNC, 03101

    opentype_r:
    .ascii "r\0"
    opentype_w:
    .ascii "w\0"

# standard file descriptors
    .equ STDIN, 0
    .equ STDOUT, 1
    .equ STDERR, 2

# system call interrupt
    .equ LINUX_SYSCALL, 0x80
    .equ END_OF_FILE, 0 # This is the return value
    # of read which means we’ve
    # hit the end of the file
    .equ NUMBER_ARGUMENTS, 2



.section .bss

# Buffer - this is where the data is loaded into
# from the data file and written from
# into the output file. This should
# never exceed 16,000 for various
# reasons.
    .equ BUFFER_SIZE, 500
    .lcomm BUFFER_DATA, BUFFER_SIZE

.section .text

# STACK POSITIONS
    .equ ST_SIZE_RESERVE, 16
    .equ ST_FD_IN, -8
    .equ ST_FD_OUT, -16
    .equ ST_ARGC, 0 # Number of arguments
    .equ ST_ARGV_0, 8 # Name of program
    .equ ST_ARGV_1, 16 # Input file name
    .equ ST_ARGV_2, 24 # Output file name

.globl _start
_start:
    movq %rsp, %rbp
    subq $ST_SIZE_RESERVE, %rsp

open_files:
open_fd_in:

    ### OPEN INPUT FILE ###
    movq ST_ARGV_1(%rbp), %rdi
    movq $opentype_r, %rsi
    call fopen

store_fd_in:
    # save the given file descriptor
    movq %rax, ST_FD_IN(%rbp)

open_fd_out:
    ###OPEN OUTPUT FILE###
    movq ST_ARGV_2(%rbp), %rdi # output filename into %ebx
    movq $opentype_w, %rsi # flags for writing to the file
    call fopen

store_fd_out:
    #store the file descriptor here
    movq %rax, ST_FD_OUT(%rbp)

### BEGIN MAIN LOOP###
read_loop_begin:
    ### READ IN A BLOCK FROM THE INPUT FILE###
    movq $BUFFER_DATA, %rdi
    movq $BUFFER_SIZE, %rsi
    movq $1, %rdx
    movq ST_FD_IN(%rbp), %rcx
    call fread

    ### CHECK IF WE’VE REACHED THE END###
    cmpq $0, %rax
    jle end_loop

continue_read_loop:
    ### CONVERT THE BLOCK TO UPPER CASE###
    movq $BUFFER_DATA, %rdi # location of buffer
    movq $BUFFER_SIZE, %rsi # size of the buffer
    call convert_to_upper

    ### WRITE THE BLOCK OUT TO THE OUTPUT FILE###
    movq $BUFFER_DATA, %rdi
    movq $BUFFER_SIZE, %rsi
    movq $1, %rdx
    movq ST_FD_OUT(%rbp), %rcx
    call fwrite

    ### CONTINUE THE LOOP ###
    jmp read_loop_begin

end_loop:
    ### CLOSE THE FILES ###
    movq ST_FD_OUT(%rbp), %rdi
    call fclose

    movq ST_FD_IN(%rbp), %rdi
    call fclose

    ### EXIT ###
    movq $SYS_EXIT, %rax
    movq $0, %rdi
    syscall
    

# PURPOSE: This function actually does the
# conversion to upper case for a block
#
# INPUT: The first parameter is the location
# of the block of memory to convert
# The second parameter is the length of
# that buffer
#
# OUTPUT: This function overwrites the current
# buffer with the upper-casified version.
#
# VARIABLES:
# %rax - beginning of buffer
# %rbx - length of buffer
# %rdi - current buffer offset
# %cl - current byte being examined
# (first part of %ecx)
#

### CONSTANTS ##
    # The lower boundary of our search
    .equ LOWERCASE_A, 'a'
    # The upper boundary of our search
    .equ LOWERCASE_Z, 'z'
    # Conversion between upper and lower case
    .equ UPPER_CONVERSION, 'A' - 'a'

convert_to_upper:
    # no need operate rsp or rbp,
    # cause we don't use stack and local variable

    movq %rdi, %rax
    movq %rsi, %rbx
    movq $0, %rdi
    # if a buffer with zero length was given
    # to us, just leave
    cmpq $0, %rbx
    je end_convert_loop

convert_loop:
    # get the current byte
    movb (%rax, %rdi, 1), %cl
    # go to the next byte unless it is between
    # ’a’ and ’z’
    cmpb $LOWERCASE_A, %cl
    jl next_byte
    cmpb $LOWERCASE_Z, %cl
    jg next_byte
    # otherwise convert the byte to uppercase
    addb $UPPER_CONVERSION, %cl
    # and store it back
    movb %cl, (%rax, %rdi, 1)

next_byte:
    incq %rdi # next byte
    cmpq %rdi, %rbx # continue unless
                    # we’ve reached the end
    jne convert_loop

end_convert_loop:
    # no return value, just leave
    ret

