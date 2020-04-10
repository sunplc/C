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

typedef unsigned packed_t;

int xbyte(packed_t word, int bytenum)
{
    return ((int) ((word >> (bytenum << 3)) << 24)) >> 24;
}

int main(int argc, char* argv[])
{
    unsigned x = 0xAA11FF66;
    int y = xbyte(x, 3);
    show_bytes((byte_pointer) &y, sizeof(int));
    y = xbyte(x, 2);
    show_bytes((byte_pointer) &y, sizeof(int));
    printf("%ld\n", sizeof(y));
    return 0;
}

