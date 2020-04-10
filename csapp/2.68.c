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

int lower_one_mask(int n)
{
    int mask = 1 << (n-1);
    return mask + mask - 1;
}

int main(int argc, char* argv[])
{
    int x = lower_one_mask(32);
    show_bytes((byte_pointer) &x, sizeof(int));
    return 0;
}

