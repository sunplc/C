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

void show_int(int a)
{
    show_bytes((byte_pointer) &a, sizeof(int));
}

void show_float(float a)
{
    show_bytes((byte_pointer) &a, sizeof(float));
}

void show_pointer(void *a)
{
    show_bytes((byte_pointer) &a, sizeof(void *));
}

int main(int argc, char *argv[])
{
    int val = 12345;
    int ival = val;
    float fval = (float) val;
    int *ip = &val;
    show_int(ival);
    show_float(fval);
    show_pointer(ip);

    //float s = 3510593;
    char *s = "abcdef";
    byte_pointer p = (byte_pointer) s;

    show_bytes(p, 6);

	return 0;
}

