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
    int bias = (sign_bit << k) - (sign_bit);
    return (x + bias) >> k;
}
    int is_neg = !!(x & INT_MIN);
    int bias = (is_neg << 2) - is_neg;

/*
 * compute 3*x/4
 */
int mul3div4(int x)
{
    int tmp = (x << 1) + x;
    tmp = divide_power2(tmp, 2);
    return tmp;
}

int main(int argc, char* argv[])
{
    int x = INT_MAX/3 + 1;
    printf("%d * 3 / 4 = %d\n", x, x*3/4);

    int z = mul3div4(x);
    printf("mul3div4(%d) = %d\n", x, z);

    return 0;
}

