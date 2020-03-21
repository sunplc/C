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

void show_float(float a)
{
    show_bytes((byte_pointer) &a, sizeof(float));
}

int main(int argc, char* argv[])
{
    float f = 1e10;
    printf("f = %f\n", f);
    show_float(f);

    long l = 0x7f800000; // positive infinity
    //long l = 0x7f800001; // NaN
    f =  * ((float *) &l);
    printf("f = %f\n", f);
    show_float(f);

    float f1, f2;
    f1 = 1.0, f2 = 2.0;
    printf("comparation: %d\n", f2 == -(-f2));

    f2 *= 121424234243123123;
    f2 *= 121424234243123123;
    f2 *= 121424234243123123;
    printf("f2 = %f\n", f2);

    f2 = 1e20 * 1e20;
    printf("%f\n", -(f2 - f2));

    l = 0x80000000;
    f2 =  * ((float *) &l);
    printf("%f\n", f2);
}

