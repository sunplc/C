# Modified to adjust my x86-64 machine

.include "linux.s"
.include "record-def.s"

.section .data
# Constant data of the records we want to write
# Each text data item is padded to the proper
# length with null (i.e. 0) bytes.
# .rept is used to pad each item. .rept tells
# the assembler to repeat the section between
# .rept and .endr the number of times specified.
# This is used in this program to add extra null
# characters at the end of each field to fill
# it up

record:
.ascii "Chris\0"
.rept 34 #Padding to 40 bytes
.byte 0
.endr

.ascii "Sun\0"
.rept 36 #Padding to 40 bytes
.byte 0
.endr

.ascii "4242 Big egg\nNew York, OK 55555\0"
.rept 208 #Padding to 240 bytes
.byte 0
.endr

.quad 0
.quad 28

.equ ST_FILE_DESCRIPTOR, -8

    msg_invalid_argc:
    .ascii "\nInvalid command-line arguments!\nUsage: ./write-identical-records test.dat\n\n\0"
    msg_len_invalid_argc:
    .quad 77



.section .text

.globl _start
_start:

    # Copy the stack pointer to %ebp
    movq %rsp, %rbp
    # Allocate space to hold the file descriptor
    addq $ST_FILE_DESCRIPTOR, %rsp

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
    
    jmp end_process

skip_argc_error:

    # Open the file
    movq $SYS_OPEN, %rax
    movq ST_ARGV_1(%rbp), %rdi
    movq $O_CREAT_WRONLY, %rsi # This says to create if it
    # doesn’t exist, and open for writing
    movq $0666, %rdx
    syscall

    # Store the file descriptor away
    movq %rax, ST_FILE_DESCRIPTOR(%rbp)

    # Save times count on the stack
    pushq $0 

    # Write the records
    # loop 30 times
start_write_loop:
    cmpq $30, -16(%rbp) 
    jge end_write_loop

    movq ST_FILE_DESCRIPTOR(%rbp), %rdi
    movq $record, %rsi
    call write_record

    incq -16(%rbp)  # Increment times count
    jmp start_write_loop

end_write_loop:

# Close the file descriptor
movq $SYS_CLOSE, %rax
movq ST_FILE_DESCRIPTOR(%rbp), %rdi
syscall

end_process:

# Exit the program
movq $SYS_EXIT, %rax
movq $0, %rdi
syscall

