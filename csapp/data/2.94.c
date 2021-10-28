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

/* Compute 0.5 * f. If f is NaN, then return f. */
float_bits float_half(float_bits f)
{
    /* Decompose bit representation into parts */
    unsigned sign = f>>31;
    unsigned exp =  f>>23 & 0xFF;
    unsigned frac = f     & 0x7FFFFF;

    unsigned is_round_to_even = (frac & 0x3) == 0x3;

    /* If is NaN or inf, then return f */
    if (exp == 0xFF) {
        return f;
    } else if (exp == 0) { /* Denormalized value */
        frac >>= 1;
        frac += is_round_to_even;
    } else { /* Normalized value */
        exp -= 1;
        /* too small, normalized to denormalized format */
        if (exp == 0) {
            frac >>= 1;
            frac = frac | 0x400000;
            frac += is_round_to_even;
        }
    }
    
    return (sign << 31) | (exp << 23) | frac;
}

int main(int argc, char* argv[])
{
    unsigned u;
    // u is NaN
    // u = 0b01111111100000000000000000000000;
    // u is Normalized value
    u = 0b00000000110000000000000000000011;
    // u is denormalized value
    //u = 0b10000000010000000000000000000001;
    // twice of u is too big, become inf
    //u = 0b11111111010000000000000000000001;

    //u=f2u(-4.3);


    float_bits f = u;

    binary_print((int)f);
    float fv = u2f(f);
    printf("%.127f\n", fv);

    f = float_half(f);
    binary_print((int)f);
    fv = u2f(f);
    printf("%.127f\n", fv);
    printf("%.127f\n", fv*2);

    return 0;
}

