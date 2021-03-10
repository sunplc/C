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
 * Compute (float) i.
 * If conversion causes overflow or f is NaN, return 0x80000000.
 *
 * round toward zero, so we just truncate fractional part of result,
 * no matter positive or negative value result is.
 */
float_bits float_i2f(int i)
{
    unsigned sign, exp = 0, frac;

    if (i < 0) {
        sign = 1;
        frac = ~i + 1;
    } else if (i > 0) {
        sign = 0;
        frac = i;
    } else {
        return 0;
    }

    /*
     * Count how many bits does frac occupied, except left hand zero bits,
     */
    unsigned digits = 0, tmp = frac;
    for (digits = 0; digits <= 32; digits++) {
        if (tmp == 0) {
            break;
        } else {
            tmp >>= 1;
        }
    }

    /* How many bits do we need to right shift */
    int rsw = digits - (23 + 1);

    /* Need right shift */
    if (rsw > 0) {
        /* Check whether need rounding */
        unsigned is_need_round = ((frac >> (rsw - 1)) & 0x3) == 0x3;
        frac >>= rsw;
        if (is_need_round) {
            /* 
             * Check whether rounding will cause frac overflow,
             * if frac overflow, then we need add one to exp
             */
            if ((frac & 0x7FFFFF) == 0x7FFFFF) {
                exp += 1;
            }
            frac += 1;
        }

    /* Need left shift */
    } else if (rsw < 0) {
        frac <<= (-rsw);
    }

    /* Clear other bits */
    frac = frac & 0x7FFFFF;

    /* Compute exp */
    exp += rsw + 23 + 127;

    return (sign << 31) | (exp << 23) | frac;
}

int main(int argc, char* argv[])
{
    int u;
    //u =  0b01111111100000000000000000000001;
    u = 0b11000000100010011001100110011010;
    //u=-4;
    u = INT_MAX;

    binary_print(u);
    printf("%d\n", u);

    float_bits f = float_i2f(u);

    binary_print(f);
    float fv = u2f(f);
    printf("%.30f\n", fv);

    puts("");

    /* Check my result with machine's floating-point operation */
    puts("Check result:");
    printf("(float) %d = %f\n", u, (float)u);
    //int x = f2u((float)u);
    //binary_print(x);

    return 0;
}

