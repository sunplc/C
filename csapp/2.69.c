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

unsigned rotate_left(unsigned x, int n)
{
    int w = sizeof(int) << 3;

    int mask = 1 << (w - n);
    mask -= 1;
    mask = ~mask;

    unsigned tmp = 0;
    tmp = x & mask;
    tmp >>= (w - n);

    x <<= n;
    return x | tmp;
}

int main(int argc, char* argv[])
{
    unsigned x = 0x12345678;
    unsigned y = rotate_left(x, 8);
    show_bytes((byte_pointer) &y, sizeof(int));
    return 0;
}

