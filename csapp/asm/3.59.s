
/*

typedef __int128 int128_t;

void store_prod(int128_t *dest, int64_t x, int64_t y)
{
    *dest = x * (int128_t) y;
}

*/

/* 
Algotithm:

P = X * Y

X = 2^64 * Xh + xl
Y = 2^64 * Yh + Yl
P = 2^64 * Ph + Pl

P = 2^64 * Xh * 2^64 *Yh 
    + 2^64 * Xh * Yl 
    + 2^64 * Yh * Xl
    + Xl * Yl
    
omit the part which overflows 128 bits, that is:

P =   2^64 * Xh * Yl 
    + 2^64 * Yh * Xl
    + Xl * Yl

store_prod:
    movq %rdx, %rax
    cqto                # copy the sign bit of rax to all the bits of rdx
                        # make y -> %rdx:%rax, Yh:Yl
    movq %rsi, %rcx
    sarq $63, %rcx      # make x -> %rcx:%rsi, Xh:Xl
    imulq %rax, %rcx
    imulq %rsi, %rdx
    addq %rdx, %rcx     # %rcx = (%rax * %rcx) + (%rsi * %rdx), tmp = Yl * Xh + Xl * Yh

    mulq %rsi           # %rdx:%rax = %rax * %rsi, P = Xl * Yl

    addq %rcx, %rdx     # %rdx = %rdx + %rcx, P = P + 2^64 * tmp
    movq %rax, (%rdi)
    movq %rdx, 8(%rdi)
    ret                 # return %rdx:%rax

