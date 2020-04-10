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

int leftmost_one(unsigned x) {
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    
    return (x >> 1) + (x && 1);
}

int main(int argc, char* argv[])
{
    unsigned x = 0x8;
    int y = leftmost_one(x);
    show_bytes((byte_pointer) &y, sizeof(int));

}

