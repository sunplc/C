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

int tsub_ok(int x, int y)
{
    y = -y;

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

    return !is_overflow;
}

int main(int argc, char* argv[])
{
    int x = -(INT_MAX>>1) - 3;
    int y = (INT_MAX>>1);
    show_bytes((byte_pointer) &x, sizeof(int));
    show_bytes((byte_pointer) &y, sizeof(int));
    printf("tsub_ok(): %d\n", tsub_ok(x, y));
    int z = x - y;
    show_bytes((byte_pointer) &z, sizeof(int));
    return 0;
}

