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

// Shift right logically
unsigned srl(unsigned x, int k) {
    // Perform shift arithmetically
    unsigned xsra = (int) x >> k;

    // get word size
    int w = sizeof(int) << 3;
    // create a mask which k most significant bits
    // are zero, the rest of bits are one
    int mask = -1;
    mask = ~(mask << (w - k));

    // make the k most significant bits of xsra equals zero
    xsra = xsra & mask;

    return xsra;
}

// Shift right arithmetically
int sra(int x, int k) {
    // Perform shift logically
    int xsrl = (unsigned) x >> k;

    // get word size
    int w = sizeof(int) << 3;

    // Check whether the most significant bit of x is zero
    if ((x & (1 << (w -1))) == 0) {
        return xsrl;
    }

    // create a mask which k most significant bits
    // are one, the rest of bits are zero
    int mask = -1;
    mask = mask << (w - k);

    // make the k most significant bits of xsrl equals one
    xsrl = xsrl | mask;

    return xsrl;
}

int main(int argc, char* argv[])
{
    unsigned x = 0xABCDABCD;
    show_bytes((byte_pointer) &x, sizeof(unsigned));
    x = srl(x, 16);
    show_bytes((byte_pointer) &x, sizeof(unsigned));
    
    int y = 0x87654321;
    show_bytes((byte_pointer) &y, sizeof(int));
    y = sra(y, 16);
    show_bytes((byte_pointer) &y, sizeof(int));

    return 0;
}

