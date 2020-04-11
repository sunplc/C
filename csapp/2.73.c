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

/* Addition that saturates to TMax or Tmin
 * saturate : 饱和
 */
int saturating_add(int x, int y)
{
    int word_size = sizeof(int)<<3;
    int sign_mask = 1 << (word_size - 1);

    // Check whether x and y is same sign
    int is_same_sign = !((x & sign_mask) ^ (y & sign_mask));

    // Get the sign of x
    int x_sign = !!(x & sign_mask);
    int z = x + y;
    // Get the sign of z
    int z_sign = !!(z & sign_mask);

    // Check is overflow
    int is_overflow = is_same_sign && (z_sign ^ x_sign);
    // printf("is_overflow: %d\n", is_overflow);
    
    // generate a is_overflow mask
    is_overflow <<= (word_size - 1);
    is_overflow >>= (word_size - 1);

    // return TMin or TMax when overflow, or return z when not overflow
    return (is_overflow & (INT_MAX + x_sign)) +  ((~is_overflow) & z);
}

int main(int argc, char* argv[])
{
    int x = INT_MAX;
    int y = INT_MAX;
    int z = saturating_add(x, y);
    show_bytes((byte_pointer) &z, sizeof(int));
    return 0;
}

