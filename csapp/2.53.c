#include <stdio.h>

// Here is very strange, when there is no 'unsigned'
typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer p, long len) {
    p = p + len - 1;
    printf("0x");
    while (len-- > 0) {
        printf("%.2x", *p--);
    }
    printf("\n");
}

#define POS_INFINITY 1.8e308
#define NEG_INFINITY -POS_INFINITY
#define NEG_ZERO -0.0

int main(int argc, char* argv[])
{
    printf("sizeof(double) = %ld\n", sizeof(double));

    double d = POS_INFINITY;
    printf("d = %lf\n", d);
    show_bytes((byte_pointer)&d, sizeof(double));

    d = NEG_INFINITY;
    printf("d = %lf\n", d);
    show_bytes((byte_pointer)&d, sizeof(double));

    d = NEG_ZERO;
    printf("d = %lf\n", d);
    show_bytes((byte_pointer)&d, sizeof(double));
}

