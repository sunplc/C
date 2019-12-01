# Modified to adjust my x86-64 machine

# Parameters:
# %rdi - fd to read
# %rsi - the address of buffer which we will 
#   read content into it

.include "linux.s"
.include "record-def.s"

.globl read_record
.type read_record, @function
read_record:

    movq $SYS_READ, %rax
    movq $RECORD_SIZE, %rdx
    syscall

    ret

