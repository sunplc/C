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

/* Replace number i byte of x by byte b.
 i start with 0 from the least significant byte */
unsigned replace_byte(unsigned x, int i, unsigned char b)
{
    // create a mask to clear the specified byte of x
    unsigned mask = 0xff;
    mask = ~(mask << i * 8);
    x = x & mask;
    // assign b to mask, shift this byte to position 
    // which specified by i
    mask = b;
    mask = mask << i * 8;
    // combine x and that byte
    return x | mask;
}

/* Get most signicant byte from x */
int get_msb(int x) {
    // Shift by w-8
    int shift_val = (sizeof(int)-1)<<3;
    // Arithmetic right shift
    int xright = x >> shift_val;
    // Zero all byte but LSB
    return xright & 0xFF;
}

int main(int argc, char* argv[])
{
    unsigned x = replace_byte(0x12345678, 1, 0xab);
    show_bytes((byte_pointer) &x, sizeof(unsigned));

    int i = INT_MIN;
    i = get_msb(i);
    show_bytes((byte_pointer) &i, sizeof(unsigned));

    return 0;
}

