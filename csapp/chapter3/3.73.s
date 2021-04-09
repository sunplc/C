
.text
.globl find_range_asm
.type find_range_asm, @function

# range_t find_range(float x)
# x in xmm0
find_range_asm:
    vxorps %xmm1, %xmm1, %xmm1  # set %xmm1 to 0
    vucomiss %xmm1, %xmm0       # compare x:0
    jp .LOC_NAN
    ja .LOC_POS
    jb .LOC_NEG
    je .LOC_ZERO

.LOC_POS:
    movl $2, %eax
    rep ret
.LOC_NEG:
    movl $0, %eax
    rep ret
.LOC_ZERO:
    movl $1, %eax
    rep ret
.LOC_NAN:
    movl $3, %eax
    rep ret

