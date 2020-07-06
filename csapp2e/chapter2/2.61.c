#include <stdio.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer p, int len) {
    p = p + len - 1;
    printf("0x ");
    while (len-- > 0) {
        printf("%.2X ", *p--);
    }
    printf("\n");
}

int main(int argc, char* argv[])
{
    // Check whether any bit of x is 1
    int x = -1;
    int rs = !~x;
    printf("Any bit of x is 1: %d\n", rs);

    // Check whether any bit of x is 0
    x = 0;
    rs = !x;
    printf("Any bit of x is 0: %d\n", rs);

    // Check whether any bit in the least
    // significant byte of x is 1
    x = 0x1FF;
    rs = !~(x | (~0xFF));
    printf("Any bit int the least significant"
            "byte of x is 1: %d\n", rs);

    // Check whether any bit in the most
    // significant byte of x is 0
    x = 34;
    rs = !(x & (0xFF<<((sizeof(int)-1)<<3)));
    printf("Any bit int the most significant"
            "byte of x is 0: %d\n", rs);
}

