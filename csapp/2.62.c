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

/** 
 * Check if this machine use arithmetic right shifts
 * or logical right shifts 
 */
int int_shifts_are_arithmetic() {
    int x = -1;
    x = x >> 1;

    // create a mask which all bits are zero 
    // except the most significant bit is one
    int mask = 1;
    mask = mask << ((sizeof(int) << 3) - 1);

    // make all bits of x equals zero except the
    // most significant bit
    x = x & mask;
    return x == mask;
}

int main(int argc, char* argv[])
{
    printf("Is arithmetic right shifts: %d\n",
        int_shifts_are_arithmetic());
    return 0;
}

