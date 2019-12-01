# Read records from file, and find the largest age

.include "linux.s"
.include "record-def.s"

.section .data
    msg_invalid_argc:
    .ascii "\nInvalid command-line arguments!\nUsage: ./find-largest-age test.dat\n\n\0"
    msg_len_invalid_argc:
    .quad 70

.section .bss
    .lcomm record_buffer, RECORD_SIZE

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
    .equ ST_HOLD_AGE, -24
    .equ ST_FIRST_TIME_FLAG, -32

    # Copy the stack pointer to %ebp
    movq %rsp, %rbp

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

    # Allocate space to hold the file descriptors
    subq $32, %rsp

    # Open the file
    movq $SYS_OPEN, %rax
    movq ST_ARGV_1(%rbp), %rdi
    movq $O_RDONLY, %rsi #This says to open read-only
    movq $0666, %rdx
    syscall

    #Save file descriptor
    movq %rax, ST_INPUT_DESCRIPTOR(%rbp)
    movq $STDOUT, ST_OUTPUT_DESCRIPTOR(%rbp)

record_read_loop:
    # Read a record to buffer
    movq ST_INPUT_DESCRIPTOR(%rbp), %rdi
    movq $record_buffer, %rsi
    call read_record

    # Returns the number of bytes read.
    # If it isn’t the same number we
    # requested, then it’s either an
    # end-of-file, or an error, so we’re
    # quitting
    cmpq $RECORD_SIZE, %rax
    jne finished_reading

    # Move the current record's age value to %rax
    movq RECORD_AGE + record_buffer, %rax

    # If this is first time to read record, then we
    # need to put age in ST_HOLD_AGE(%rbp) on the stack
    cmpq $1, ST_FIRST_TIME_FLAG(%rbp)
    je skip_first_time_assign
    movq %rax, ST_HOLD_AGE(%rbp)
    movq $1, ST_FIRST_TIME_FLAG(%rbp)

skip_first_time_assign:

    cmpq %rax, ST_HOLD_AGE(%rbp)
    jge skip_age_assign             # Find maximux age
    # jle skip_age_assign           # Find minimum age
    movq %rax, ST_HOLD_AGE(%rbp)

skip_age_assign:

jmp record_read_loop

finished_reading:
    movq ST_HOLD_AGE(%rbp), %rdi
    movq $SYS_EXIT, %rax
    syscall

