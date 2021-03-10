#include <stdio.h>
#include <limits.h>

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

    // INT_MAX + 1 等于 INT_MIN
    // INT_MIN - 1 等于 INT_MAX
    int i = INT_MAX + 1;

    printf("INT_MAX + 1 = %d:\t", i);
    show_bytes((byte_pointer) &i, sizeof(i));

    i = INT_MIN - 1;
    printf("INT_MIN - 1 = %d:\t", i);
    show_bytes((byte_pointer) &i, sizeof(i));

    short sx = -12345;
    unsigned short usx = sx;
    int x = sx;
    unsigned ux = usx;

    printf("sx = %d:\t", sx);
    show_bytes((byte_pointer) &sx, sizeof(short));
    printf("sx = %d:\t", usx);
    show_bytes((byte_pointer) &usx, sizeof(unsigned short));
    printf("sx = %d:\t", x);
    show_bytes((byte_pointer) &x, sizeof(int));
    printf("sx = %d:\t", ux);
    show_bytes((byte_pointer) &ux, sizeof(unsigned));

}

