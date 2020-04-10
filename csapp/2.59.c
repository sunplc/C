#include <stdio.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer p, int len) {
    p = p + len - 1;
    printf("0x ");
    while (len-- > 0) {
        printf("%.2x ", *p--);
    }
    printf("\n");
}

int main(int argc, char* argv[])
{
    int x = 0x89ABCDEF;
    int y = 0x76543210;

    int z = (x & 0x000000ff) | (y & 0xffffff00);

    show_bytes((byte_pointer) &z, sizeof(int));
}

