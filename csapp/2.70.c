#include <stdio.h>
#include <limits.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer p, int len) {
    p = p + len - 1;
    printf("0x ");
    while (len-- > 0) {
        printf("%.2X ", *p--);
    }
    printf("\n");
}

/* 
 * Return 1 when x can be represented as an n-bit,
 * 2's complement number; 0 otherwise
 * Assume 1 <= n < w
 */
int fits_bits(int x, int n)
{
    // Get bit size of int
    int w = sizeof(int) << 3;
    
    // Generate a mask with all bits equals zero
    // when x is positive number, or with all bits
    // equals one when x is negative number
    int mask = 1 << (w - 1);
    mask = x & mask;
    mask >>= (w - 1);

    // Perform the NOT operation on x when x is negative,
    // Or do nothing when x is positive
    x = x ^ mask;

    // Generate another mask with n-1 least significant bits 
    // equals zero, and the rest bits of mask equals one.
    mask = 1 << (n - 1);
    mask -= 1;
    mask = ~mask;

    // Determine whether mask can cover the x, if so it
    // means that n-bit can represent x 
    return !(mask & x);
}

int main(int argc, char* argv[])
{
    int x = -0xFF;
    printf("fits_bits() = %d\n", fits_bits(x, 9));
    return 0;
}

