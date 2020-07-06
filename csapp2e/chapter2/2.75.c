#include <stdio.h>
#include <limits.h>
#include <inttypes.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer p, int len) {
    p = p + len - 1;
    printf("0x ");
    while (len-- > 0) {
        printf("%.2X ", *p--);
    }
    printf("\n");
}

int signed_high_prod(int x, int y) {
    unsigned word_size = sizeof(int)<<3;
    //long z = (long)x;
    //show_bytes((byte_pointer) &z, sizeof(long));
    return (int) (((long)x * y) >> word_size);
}

unsigned int unsigned_high_prod(unsigned x, unsigned y)
{
    unsigned word_size = sizeof(int)<<3;
    unsigned sign_mask = 1 << (word_size - 1);

    unsigned x_sign = !!(x & sign_mask);
    unsigned y_sign = !!(y & sign_mask);

    return signed_high_prod(x, y) + 
        (x_sign * y + x * y_sign);
}

// Directly compute the unsigned high order w-bits of product
unsigned direct_unsigned_high_prod(unsigned x, unsigned y)
{
    unsigned word_size = sizeof(int)<<3;
    //unsigned long z = (unsigned long)x;
    //show_bytes((byte_pointer) &z, sizeof(long));
    return (unsigned) (((unsigned long)x * y) >> word_size);
}

/*
 * 假设 long 的长度是 int 的两倍
 */
int main(int argc, char* argv[])
{
    puts("\nx and y :");
    int x = -(INT_MAX>>1) - 3;
    int y = (INT_MAX>>1);
    show_bytes((byte_pointer) &x, sizeof(int));
    show_bytes((byte_pointer) &y, sizeof(int));

    puts("\nsigned_high_prod(x, y) = ");

    int z = signed_high_prod(x, y);
    show_bytes((byte_pointer) &z, sizeof(int));

    unsigned ux = x;
    unsigned uy = y;
    puts("\nunsigned_high_prod(x, y) = ");
    unsigned uz = unsigned_high_prod(ux, uy);
    show_bytes((byte_pointer) &uz, sizeof(int));

    puts("\ndirect_unsigned_high_prod(x, y) = ");
    uz = direct_unsigned_high_prod(ux, uy);
    show_bytes((byte_pointer) &uz, sizeof(int));
    return 0;
}

