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
 * Divide by power of two
 */
int divide_power2(int x, int k)
{
    //return x >> k;

    int sign_bit = ((unsigned) x) >> ((sizeof(int) << 3) - 1);
    int bias = (sign_bit << k) - (sign_bit && 1);
    return (x + bias) >> k;
}

int main(int argc, char* argv[])
{
    int x = -12340;
    int k = 8;
    int z = divide_power2(x, k);
    printf("divide_power2(%d, %d) = %d\n", x, k, z);
    show_bytes((byte_pointer) &z, sizeof(int));
    return 0;
}

