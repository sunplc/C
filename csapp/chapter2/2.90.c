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

void show_float(float a)
{
    show_bytes((byte_pointer) &a, sizeof(float));
}

/* Returns a floating-point value having an identical
 * bit representation as its unsigned argument
 */
float u2f(unsigned u)
{
    return *(float *) &u;
}

int main(int argc, char* argv[])
{
    unsigned p = 0x40490FDB;
    float pai = u2f(p);
    printf("pai = %f %g\n", pai, pai);

    // 11.001001001...
    float f = 22/7.0;
    printf("22/7 = %f %f\n", f, f);
    show_float(0.7);

    return 0;
}

