# include allocator define file
.include "alloc.s"

# Read records from file

.include "linux.s"
.include "record-def.s"

.section .data
    msg_invalid_argc:
    .ascii "\nInvalid command-line arguments!\nUsage: ./read-records test.dat\n\n\0"
    msg_len_invalid_argc:
    .quad 66

.section .bss
    .lcomm record_buffer_ptr, 8

.section .text
# Main program
.globl _start
_start:
    # These are the locations on the stack where
    # we will store the input and output descriptors
    # (FYI - we could have used memory addresses in
    # a .data section instead)
    .equ ST_INPUT_DESCRIPTOR, -8
    .equ ST_OUTPUT_DESCRIPTOR, -16

    # function allocate_init will be called in
    # function allocate automatically
    # call allocate_init

    movq $RECORD_SIZE, %rdi
    call allocate

    movq %rax, record_buffer_ptr

    # Copy the stack pointer to %ebp
    movq %rsp, %rbp
    # Allocate space to hold the file descriptors
    subq $16, %rsp

    # Check argc
    cmpq $2, ST_ARGC(%rbp)
    jne invalid_argc_exit

    jmp skip_argc_error

invalid_argc_exit:

    # Write error msg and exit
    movq $SYS_WRITE, %rax
    movq $STDERR, %rdi
    movq $msg_invalid_argc, %rsi
    movq msg_len_invalid_argc, %rdx
    syscall
    
    jmp finished_reading

skip_argc_error:

    # Open the file
    movq $SYS_OPEN, %rax
    movq ST_ARGV_1(%rbp), %rdi
    movq $O_RDONLY, %rsi # This says to open read-only
    movq $0666, %rdx
    syscall

    #Save file descriptor
    movq %rax, ST_INPUT_DESCRIPTOR(%rbp)
    movq $STDOUT, ST_OUTPUT_DESCRIPTOR(%rbp)

record_read_loop:
    # Read a record to buffer
    movq ST_INPUT_DESCRIPTOR(%rbp), %rdi
    movq record_buffer_ptr, %rsi
    call read_record

    # Returns the number of bytes read.
    # If it isn’t the same number we
    # requested, then it’s either an
    # end-of-file, or an error, so we’re
    # quitting
    cmpq $RECORD_SIZE, %rax
    jne finished_reading

    # Otherwise, print out the first name
    # but first, we must know it’s size
    movq record_buffer_ptr, %rdi
    addq $RECORD_FIRSTNAME, %rdi
    call count_chars

    # print out first name
    movq %rax, %rdx
    movq $SYS_WRITE, %rax
    movq ST_OUTPUT_DESCRIPTOR(%rbp), %rdi
    movq record_buffer_ptr, %rsi
    addq $RECORD_FIRSTNAME, %rsi
    syscall

    # Write a character newline ('\n') to STDOUT
    movq ST_OUTPUT_DESCRIPTOR(%rbp), %rdi
    call write_newline

jmp record_read_loop

finished_reading:
    movq record_buffer_ptr, %rdi
    call deallocate

    movq $SYS_EXIT, %rax
    movq $0, %rdi
    syscall

