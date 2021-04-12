
.text
.globl find_range_asm
.type find_range_asm, @function

# range_t find_range(float x)
# x in xmm0
find_range_asm:

    vxorps %xmm1, %xmm1, %xmm1  # set %xmm1 to 0
    vucomiss %xmm1, %xmm0       # compare x:0

    movl $0, %r8d
    movl $1, %r9d
    movl $2, %r10d
    movl $3, %r11d

    cmovb %r8d, %eax
    cmove %r9d, %eax
    cmova %r10d, %eax
    cmovp %r11d, %eax

    rep ret

