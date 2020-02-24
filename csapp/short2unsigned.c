#include <stdio.h>

typedef unsigned char* byte_pointer;

void show_bytes(byte_pointer p, int len) {
    p = p + len - 1;
    printf("0x");
    while (len-- > 0) {
        printf("%.2x", *p--);
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    short sx = -12345;
    //unsigned uy = (unsigned) (unsigned short) sx;
    unsigned uy = sx;

    printf("uy = %u:\t", uy);
    show_bytes((byte_pointer) &uy, sizeof(uy));

}

