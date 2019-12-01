# Constant of Linux syscall

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
    .equ O_WRONLY, 1
    .equ O_RDWR, 2
    .equ O_CREAT_WRONLY_TRUNC, 03101
    .equ O_CREAT_WRONLY, 0101

# Constants for lseek syscall
    .equ SEEK_SET, 0
    .equ SEEK_CUR, 1
    .equ SEEK_END, 2

# standard file descriptors
    .equ STDIN, 0
    .equ STDOUT, 1
    .equ STDERR, 2

# Initial Process Stack layout
    .equ ST_ARGC, 0 # Number of arguments
    .equ ST_ARGV_0, 8 # Name of program
    .equ ST_ARGV_1, 16 # Input file name
    .equ ST_ARGV_2, 24 # Output file name
