# Modified to adjust my x86-64 machine

# Parameters:
# %rdi - fd to write
# %rsi - the memory address of record to write

.include "linux.s"
.include "record-def.s"

.globl write_record
.type write_record, @function
write_record:

    movq $SYS_WRITE, %rax
    movq $RECORD_SIZE, %rdx
    syscall

    ret

