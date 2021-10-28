
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

    # if *start is negative value,
    # transform *start to positive value.
    andq %r10, %r10
    jge add
    xorq %r11, %r10
    addq %r12, %r10
add:
    addq %r10,%rax 
    addq %r8,%rdi
    subq %r9,%rsi
test:
    jne loop_start
    ret 
