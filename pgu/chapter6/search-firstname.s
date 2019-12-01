# Allow user input 5 characters, and output all records
# whose firstname start with these 5 characters

.include "linux.s"
.include "record-def.s"

.section .data
    msg_invalid_argc:
    .ascii "\nInvalid command-line arguments!\nUsage: ./compare-firstname test.dat\n\n\0"
    msg_len_invalid_argc:
    .quad 71

    input_tip:
    .ascii "\nPlease input 5 characters to search firstname:\n"
    input_tip_len:
    .quad 48

.section .bss
    .lcomm record_buffer, RECORD_SIZE

    .equ compare_pattern_len, 5
    .lcomm compare_pattern, 6

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

    # Copy the stack pointer to %ebp
    movq %rsp, %rbp
    # Allocate space to hold the file descriptors
    addq $ST_OUTPUT_DESCRIPTOR, %rsp

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

    # Prompt user to input 5 characters
    movq $SYS_WRITE, %rax
    movq $STDOUT, %rdi
    movq $input_tip, %rsi
    movq input_tip_len, %rdx
    syscall

    # Wait user input 5 characters,
    # Save pattern to memory location in .BSS
    movq $SYS_READ, %rax
    movq $STDIN, %rdi
    movq $compare_pattern, %rsi
    movq $compare_pattern_len, %rdx
    syscall

    # Write a character newline ('\n') to STDOUT
    movq ST_OUTPUT_DESCRIPTOR(%rbp), %rdi
    call write_newline

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

    # Compare firstname with pattern
    movq $compare_pattern, %rax
    movq $record_buffer, %rdi
    call compare_string
    cmpq $0, %rax
    je record_read_loop

    # Otherwise, print out the first name
    # but first, we must know it’s size
    movq $RECORD_FIRSTNAME + record_buffer, %rdi
    call count_chars

    # print out first name
    movq %rax, %rdx
    movq $SYS_WRITE, %rax
    movq ST_OUTPUT_DESCRIPTOR(%rbp), %rdi
    movq $RECORD_FIRSTNAME + record_buffer, %rsi
    syscall

    # Write a character newline ('\n') to STDOUT
    movq ST_OUTPUT_DESCRIPTOR(%rbp), %rdi
    call write_newline

jmp record_read_loop

finished_reading:
    movq $SYS_EXIT, %rax
    movq $0, %rdi
    syscall

# Function compare_string
# Purpose: Compare two string with first 5 characters
#
# Parameters:
# %rax - address of first string
# %rdi - address of second string
# 
# Return value:
# return 1 when match, 0 when not match
# 
.type compare_string, @function
compare_string:

movq $0, %rsi # counter

compare_loop_start:

    cmpq $5, %rsi
    je match_return

    cmpq $0, (%rax, %rsi, 1)
    je not_match_return
    cmpq $0, (%rdi, %rsi, 1)
    je not_match_return

    # Because of instruction 'cmp' can not directly
    # compare two values in memory references, so I use
    # register %dl to hold one value in memory reference, and
    # compare another value in memory reference with %dl
    movb (%rdi, %rsi, 1), %dl
    cmpb (%rax, %rsi, 1), %dl
    jne not_match_return

    addq $1, %rsi
    jmp compare_loop_start

match_return:

    movq $1, %rax
    ret

not_match_return:
    movq $0, %rax
    ret

