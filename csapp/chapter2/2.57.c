#include <stdio.h>

// Here is very strange, when there is no 'unsigned'
typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer p, int len) {
    p = p + len - 1;
    printf("0x ");
    while (len-- > 0) {
        printf("%.2x ", *p--);
    }
    printf("\n");
}

void show_short(short a)
{
    show_bytes((byte_pointer) &a, sizeof(short));
}

void show_int(int a)
{
    show_bytes((byte_pointer) &a, sizeof(int));
}

void show_long(long a)
{
    show_bytes((byte_pointer) &a, sizeof(long));
}

void show_float(float a)
{
    show_bytes((byte_pointer) &a, sizeof(float));
}

void show_double(double a)
{
    show_bytes((byte_pointer) &a, sizeof(double));
}

void show_pointer(void *a)
{
    show_bytes((byte_pointer) &a, sizeof(void *));
}

int main(int argc, char *argv[])
{
    short s = 32768;
    printf("short = %d\n", s);
    show_short(s);

    long l = -1;
    printf("long = %ld\n", l);
    show_long(l);

    double d = 1000.1;
    printf("double = %lf\n", d);
    show_double(d);
}

