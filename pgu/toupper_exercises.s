# x86_64 version of the book's example and exercises

# EXERCISE: Modify the toupper program so that it reads from 
# STDIN and writes to STDOUT instead of using the files on 
# the command-line

# EXERCISE: Change the size of the buffer

# EXERCISE: Rewrite the program so that it uses storage in 
# the .bss section rather than the stack to store the file
# descriptors

# EXERCISE: Make the program able to either operate on 
# command-line arguments or use STDIN or STDOUT based
# on the number of command-line arguments specified by ARGC.

# EXERCISE: Modify the program so that it checks the 
# results of each system call, and prints out an 
# error message to STDOUT when it occurs.

# NOTE:
# 1) use syscall instruction, instead of int instruction
# 2) use eightbyte register and instruction ,
#       instead of fourbyte register
# 3) use register to hold function arguments, instead of stack


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
    # used for syscall error check, in case of file not exist
    .equ O_WRONLY_TRUNC, 03001

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

# error message for print to STDOUT
    errmsg:
    .ascii "\nSyscall error, got an negative return value!\n"
    .equ ERRMSG_LEN, 46

.section .bss

# Buffer - this is where the data is loaded into
# from the data file and written from
# into the output file. This should
# never exceed 16,000 for various
# reasons.
    .equ BUFFER_SIZE, 5
    .lcomm BUFFER_DATA, BUFFER_SIZE

    .equ FD_SIZE, 8
    .lcomm BSS_FD_IN, FD_SIZE
    .lcomm BSS_FD_OUT, FD_SIZE

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
    ### INITIALIZE PROGRAM ###
    # save the stack pointer
    movq %rsp, %rbp

    # check to decide use command-line argument or use stdin/stdout file
    # as input/output file.
    cmpq $3, ST_ARGC(%rbp)
    jne open_files_from_stdio

open_files_from_argv:

open_fd_in:
    ### OPEN INPUT FILE ###
    movq $SYS_OPEN, %rax # open syscall
    movq ST_ARGV_1(%rbp), %rdi # input filename into %rdi
    movq $O_RDONLY, %rsi # read-only flag
    movq $0666, %rdx # this doesn’t really matter for reading
    syscall # call linux kernel on x86_64

store_fd_in:
    # save the given file descriptor
    movq %rax, BSS_FD_IN

open_fd_out:
    ###OPEN OUTPUT FILE###
    movq $SYS_OPEN, %rax # open the file
    movq ST_ARGV_2(%rbp), %rdi # output filename into %ebx
    movq $O_CREAT_WRONLY_TRUNC, %rsi # flags for writing to the file
    movq $0666, %rdx # mode for new file (if it’s created)
    syscall # call linux kernel on x86_64

    pushq %rax
    call check_error # check syscall return value
    popq %rax

store_fd_out:
    #store the file descriptor here
    movq %rax, BSS_FD_OUT

    # jump over the "open_files_from_stdio" section
    jmp read_loop_begin

open_files_from_stdio:
    movq $STDIN, BSS_FD_IN
    movq $STDOUT, BSS_FD_OUT

### BEGIN MAIN LOOP###
read_loop_begin:
    ### READ IN A BLOCK FROM THE INPUT FILE###
    movq $SYS_READ, %rax
    movq BSS_FD_IN, %rdi # get the input file descriptor
    movq $BUFFER_DATA, %rsi # the location to read into
    movq $BUFFER_SIZE, %rdx # the size of the buffer
    # Size of buffer read is returned in %eax
    syscall

    ### EXIT IF WE’VE REACHED THE END###
    # check for end of file marker
    cmpq $END_OF_FILE, %rax
    # if found or on error, go to the end
    jle end_loop

continue_read_loop:
    ### CONVERT THE BLOCK TO UPPER CASE###
    movq $BUFFER_DATA, %rdi # location of buffer
    movq %rax, %rsi # size of the buffer
    pushq %rax
    call convert_to_upper
    popq %rax # get the size back

    ### WRITE THE BLOCK OUT TO THE OUTPUT FILE###
    movq %rax, %rdx # size of the buffer,
                    # must do this before save value to rax
    movq $SYS_WRITE, %rax
    movq BSS_FD_OUT, %rdi # file to use
    movq $BUFFER_DATA, %rsi # location of the buffer
    syscall

    ### CONTINUE THE LOOP ###
    jmp read_loop_begin

end_loop:
    ### CLOSE THE FILES ###
    # NOTE - we don’t need to do error checking
    # on these, because error conditions
    # don’t signify anything special here
    movq $SYS_CLOSE, %rax
    movq BSS_FD_IN, %rdi
    syscall

    movq $SYS_CLOSE, %rax
    movq BSS_FD_OUT, %rdi
    syscall

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

# 检查 %rax 为负值，则输出一条错误信息
check_error:
    cmpq $0, %rax
    jge function_end

    movq $SYS_WRITE, %rax
    movq $STDOUT, %rdi # file to use
    movq $errmsg, %rsi # location of the buffer
    movq $ERRMSG_LEN, %rdx # size of the buffer,
    syscall

    function_end:
    ret

