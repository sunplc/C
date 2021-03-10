#include <stdio.h>
#include <limits.h>

/* Returns a floating-point value having an identical
 * bit representation as its unsigned argument
 */
float u2f(unsigned u)
{
    return *(float *) &u;
}

unsigned f2u(float f)
{
    return *(unsigned *) &f;
}

void binary_print(int x)
{
    int len = sizeof(int) * 8;
	int i, arr[len];

	for (i = 0; i < len; i++) {
		if ((x & 0x00000001) == 1)
			arr[i] = 1;
		else
			arr[i] = 0;
		x = x >> 1;
	}

	for (i = len; i > 0; i--) {
		if (i < len && i % 8 == 0)
			putchar(' ');
		printf("%d", arr[i-1]);	
	}

	putchar('\n');
}

typedef unsigned float_bits;

/* 
 * Compute (int) f.
 * If conversion causes overflow or f is NaN, return 0x80000000.
 *
 * round toward zero, so we just truncate fractional part of result,
 * no matter positive or negative value result is.
 */
int float_f2i(float_bits f)
{
    /* Decompose bit representation into parts */
    unsigned sign = f>>31;
    unsigned exp =  f>>23 & 0xFF;
    unsigned frac = f     & 0x7FFFFF;

    /* If is NaN or inf, then return f */
    if (exp == 0xFF) {
        return 0x80000000;
    } else if (exp == 0) { /* Denormalized value */
        return 0;
    } else { /* Normalized value */

        frac = frac | 0x800000;
        int e = exp - 127;
        int shift_width = e - 23;

        /* if shift_width equals 0, then don't need shift */
        if (shift_width > 0) {
            if (shift_width > 7) {
                return 0x80000000;
            } else {
                frac = frac << shift_width;
            }
        } else if (shift_width < 0) {
            if (shift_width < -23) {
                return 0;
            } else {
                frac = frac >> (-shift_width);
            }
        }

        /* If f is negative, make it bitwise NOT and add 1. */
        if (sign) {
            frac = ~frac + 1;
        }
        return (sign << 31) | frac;
    }
}

int main(int argc, char* argv[])
{
    unsigned u;
    // u is NaN
    // u =  0b01111111100000000000000000000001;
    // u is Normalized value
    u =     0b11001111100000000000000000000011;
    // u is denormalized value
    //u =   0b10000000010000000000000000000001;
    // inf
    //u =   0b11111111010000000000000000000001;

    //u=f2u(-4.3);


    float_bits f = u;

    binary_print((int)f);
    float fv = u2f(f);
    printf("%.30f\n", fv);

    int x = float_f2i(f);
    binary_print(x);
    printf("%d\n", x);

    /* Check my result with machine's floating-point operation */
    puts("Check result:");
    printf("(int) %f = %d\n", fv, (int)fv);

    return 0;
}

