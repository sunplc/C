# Modified to adjust my x86-64 machine

# Read each record from file, and increment the year field,
# and write new record to specified file

.include "linux.s"
.include "record-def.s"

.section .data
    msg_invalid_argc:
    .ascii "\nInvalid command-line arguments!\nUsage: ./add-year test.dat\n\n\0"
    msg_len_invalid_argc:
    .quad 62

    errmsg:
    .ascii "Open file failed!\n"
    .equ ERRMSG_LEN, 18

.section .bss
    .lcomm record_buffer, RECORD_SIZE

    # Stack offsets of local variables 
    .equ ST_FILE_DESCRIPTOR, -8

.section .text
.globl _start
_start:

    # Copy the stack pointer to %ebp
    movq %rsp, %rbp
    # Allocate space to hold the file descriptors
    subq $8, %rsp

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
    
    jmp loop_end

skip_argc_error:

    # Open the file for read
    movq $SYS_OPEN, %rax
    movq ST_ARGV_1(%rbp), %rdi
    movq $O_RDWR, %rsi #This says to open read-only
    movq $0666, %rdx
    syscall

    # Check if there is Open file error
    cmpq $0, %rax
    jge skip_print_error
    movq $errmsg, %rax
    movq $ERRMSG_LEN, %rdi
    call print_error

skip_print_error:


    # Save file descriptor
    movq %rax, ST_FILE_DESCRIPTOR(%rbp)

loop_begin:
    movq ST_FILE_DESCRIPTOR(%rbp), %rdi
    movq $record_buffer, %rsi
    call read_record

    # Returns the number of bytes read.
    # If it isn’t the same number we
    # requested, then it’s either an
    # end-of-file, or an error, so we’re
    # quitting
    cmpq $RECORD_SIZE, %rax
    jne loop_end

    # Increment the age
    incq record_buffer + RECORD_AGE

    # Call lseek to go back to the start position 
    # of this record, lseek return non-negative value
    # which is offset after move when succeed, or
    # -1 when failed
    movq $8, %rax
    movq ST_FILE_DESCRIPTOR(%rbp), %rdi
    # Move the offset to %rdx as parameter, remember
    # to pass the negative value cause we want go back
    movq $-RECORD_SIZE, %rsi
    movq $SEEK_CUR, %rdx
    syscall

    # Write the record out
    movq ST_FILE_DESCRIPTOR(%rbp), %rdi
    movq $record_buffer, %rsi
    call write_record
    
    jmp loop_begin

loop_end:

    movq $SYS_EXIT, %rax
    movq $0, %rdi
    syscall

