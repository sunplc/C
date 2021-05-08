
# Y86-64 code
# long absSum(long *start, long count)
# start in %rdi, count in %rsi

absSum:
    irmovq $8,%r8
    irmovq $1,%r9
    irmovq $-1, %r11
    irmovq $1, %r12

    xorq %rax,%rax
    andq %rsi,%rsi 
    jmp test

loop_start:
    mrmovq (%rdi), %r10

    # conditional move -1 * (%r10) to %r10
    rrmovq %r10, %r13
    xorq %r11, %r13
    addq %r12, %r13

    andq %r10, %r10
    cmovl %r13, %r10
    
    addq %r10,%rax 
    addq %r8,%rdi
    subq %r9,%rsi
test:
    jne loop_start
    ret 
