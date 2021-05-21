# Y86-64 assembly code

    .text

jump_table:
    .quad casedef   # -1
    .quad case0     # 0
    .quad casedef   # 1
    .quad case2     # 2
    .quad case3     # 3
    .quad casedef   # 4
    .quad case2     # 5
    .quad casedef   # 6

    .globl switchv
    .type switchv, @function
switchv:
    xorq %rax, %rax

    addq $1, %rdi


    irmovq jump_table, %r8
    irmovq $8, %r9
    irmovq $1, %r10

    # 实现 leaq jump_table(,%rdi,8), %r8
multiply_start:
    andq %rdi, %rdi
    jle multiply_end
    addq %r9, %r8
    subq %r10, %rdi
    jmp multiply_start
multiply_end:

    push %r8
    rep ret

case0:
    irmovq $0xaaa, %rax
    rep ret
case2:
    irmovq $0xbbb, %rax
    rep ret
case3:
    irmovq $0xccc, %rax
    rep ret
casedef:
    irmovq $0xddd, %rax

    rep ret

main:
