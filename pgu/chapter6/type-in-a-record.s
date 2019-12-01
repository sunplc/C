# Modified to adjust my x86-64 machine

# Read each record from file, and increment the year field,
# and write new record to specified file

.include "linux.s"
.include "record-def.s"

.section .data
    msg_invalid_argc:
    .ascii "\nInvalid command-line arguments!\nUsage: ./type-in-a-record test.dat\n\n\0"
    msg_len_invalid_argc:
    .quad 70

    errmsg:
    .ascii "Open file failed!\n"
    .equ ERRMSG_LEN, 18

    msg_over_length:
    .ascii "The string that you typed in is too long or to short, Please type again!\n"
    .equ msg_len_over_length, 73

.section .bss
    .lcomm record_buffer, RECORD_SIZE

    # Stack offsets of local variables 
    .equ ST_FILE_DESCRIPTOR, -8

    default_sex_age:
    .quad 0
    .quad 25

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
    
    jmp type_in_end

skip_argc_error:

    # Open the file for write record in
    movq $SYS_OPEN, %rax
    movq ST_ARGV_1(%rbp), %rdi
    movq $O_CREAT_WRONLY, %rsi # This says to open write-only
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

    # Call lseek to go to the end of the file
    movq $8, %rax
    movq ST_FILE_DESCRIPTOR(%rbp), %rdi
    movq $0, %rsi
    movq $SEEK_END, %rdx
    syscall

type_in_firstname:

    # Get the first name from STDIN
    movq $SYS_READ, %rax
    movq $STDIN, %rdi
    movq $record_buffer, %rsi
    movq $RECORD_LASTNAME - RECORD_FIRSTNAME, %rdx
    syscall

    # Check input length
    movq $RECORD_LASTNAME - RECORD_FIRSTNAME, %rdi
    call check_input_length
    cmpq $1, %rax
    je type_in_firstname

    # count chars
    movq $RECORD_FIRSTNAME + record_buffer, %rdi
    call count_chars

    # Write the record out
    movq %rax, %rdx
    # Remove the newline which at the end of input
    subq $1, %rdx
    pushq %rdx
    movq $SYS_WRITE, %rax
    movq ST_FILE_DESCRIPTOR(%rbp), %rdi
    movq $record_buffer, %rsi
    syscall

    # Call lseek to go to end position of field
    movq $8, %rax
    movq ST_FILE_DESCRIPTOR(%rbp), %rdi
    popq %rdx
    movq $RECORD_LASTNAME - RECORD_FIRSTNAME, %rsi
    subq %rdx, %rsi
    movq $SEEK_CUR, %rdx
    syscall

type_in_lastname:

    movq $SYS_READ, %rax
    movq $STDIN, %rdi
    movq $record_buffer + RECORD_LASTNAME, %rsi
    movq $RECORD_ADDRESS - RECORD_LASTNAME, %rdx
    syscall

    # Check input length
    movq $RECORD_ADDRESS - RECORD_LASTNAME, %rdi
    call check_input_length
    cmpq $1, %rax
    je type_in_lastname

    # count chars
    movq $record_buffer + RECORD_LASTNAME, %rdi
    call count_chars

    # Write the record out
    movq %rax, %rdx
    # Remove the newline which at the end of input
    subq $1, %rdx
    pushq %rdx
    movq $SYS_WRITE, %rax
    movq ST_FILE_DESCRIPTOR(%rbp), %rdi
    movq $record_buffer + RECORD_LASTNAME, %rsi
    syscall

    # Call lseek to go to end position of field
    movq $8, %rax
    movq ST_FILE_DESCRIPTOR(%rbp), %rdi
    popq %rdx
    movq $RECORD_ADDRESS - RECORD_LASTNAME, %rsi
    subq %rdx, %rsi
    movq $SEEK_CUR, %rdx
    syscall

type_in_address:

    movq $SYS_READ, %rax
    movq $STDIN, %rdi
    movq $record_buffer + RECORD_ADDRESS, %rsi
    movq $RECORD_SEX - RECORD_ADDRESS, %rdx
    syscall

    # Check input length
    movq $RECORD_SEX - RECORD_ADDRESS, %rdi
    call check_input_length
    cmpq $1, %rax
    je type_in_lastname

    # count chars
    movq $record_buffer + RECORD_ADDRESS, %rdi
    call count_chars

    # Write the record out
    movq %rax, %rdx
    # Remove the newline which at the end of input
    subq $1, %rdx
    pushq %rdx
    movq $SYS_WRITE, %rax
    movq ST_FILE_DESCRIPTOR(%rbp), %rdi
    movq $record_buffer + RECORD_ADDRESS, %rsi
    syscall

    # Call lseek to go to end position of field
    movq $8, %rax
    movq ST_FILE_DESCRIPTOR(%rbp), %rdi
    popq %rdx
    movq $RECORD_SEX - RECORD_ADDRESS, %rsi
    subq %rdx, %rsi
    movq $SEEK_CUR, %rdx
    syscall

    # Save default value as Sex and Age field
    movq $SYS_WRITE, %rax
    movq ST_FILE_DESCRIPTOR(%rbp), %rdi
    movq $default_sex_age, %rsi
    movq $RECORD_SIZE - RECORD_SEX, %rdx
    syscall

type_in_end:

    movq $SYS_EXIT, %rax
    movq $0, %rdi
    syscall

# function
.type check_input_length, @function
check_input_length:

    cmpq $1, %rax
    jle print_invalid_input_length

    cmpq %rdi, %rax
    jge print_invalid_input_length

    movq $0, %rax
    ret

    print_invalid_input_length:

    movq $msg_over_length, %rax
    movq $msg_len_over_length, %rdi
    call print_error

    movq $1, %rax
    ret

