#include <stdio.h>

/* Returns a floating-point value having an identical
 * bit representation as its unsigned argument
 */
float u2f(unsigned u)
{
    return *(float *) &u;
}

/* 
 * cast 2^x to IEEE single-precision represetation 
 * total 32 bit, signe = 1 bit, exp = 8 bit, fraction = 23 bit
 * bias = 127
 */
float fpwr2(int x)
{
    /* Result exponent and fraction */
    unsigned exp, frac;
    unsigned u;

    /* 126 + 23 */
    if (x < -149) {
        /* Too small. Return 0.0 */
        exp = 0;
        frac = 0;
    } else if (x < -126) {
        /* Denormalized result. */
        exp = 0;
        frac = 1 << (149 + x);
    } else if (x < 127) {
        /* Normalized result. */
        exp = x + 127;
        frac = 0;
    } else {
        /* Too big. Return +00 */
        exp = 255;
        frac = 0;
    }

    /* Pack exp and frac into 32 bit */
    u = exp << 23 | frac;
    /* Return as float */
    return u2f(u);
}

int main(int argc, char* argv[])
{
    //           0b10000000010000000000000000000000;
    unsigned u = 0b00111111100000000000000000000000;
    float f = u2f(u);
    printf("%f %g\n", f, f);

    f = fpwr2(10);
    printf("%f %g\n", f, f);

    return 0;
}

