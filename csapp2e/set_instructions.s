
.section .text
.globl _start

_start:

    movl $1, %eax
    movl $2, %edx

    // Set %al to 1, if %eax less than %edx;
    // otherwise set %al to 0, if %eax not less than %edx
    cmpl %edx, %eax
    setl %al
    movzbl %al, %eax

    // Use system call to exit process,
    // the exit code should set in register %edi
    movl %eax, %edi
    movl $60, %eax
    syscall

