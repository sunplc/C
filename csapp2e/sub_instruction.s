
.globl _start

_start:


    // x = x - 3;
    movl $10, %eax
    leal -3(%eax), %eax

    // Use system call to exit process,
    // the exit code should set in register %edi
    movl %eax, %edi
    movl $60, %eax
    syscall

