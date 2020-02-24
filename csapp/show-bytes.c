#include <stdio.h>

// Here is very strange, when there is no 'unsigned'
typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start_addr, long len) {
    int i;
    for (i = 0; i < len; i++) {
        printf("%.2x ", start_addr[i]);
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

void test_show_bytes(int val)
{
    int ival = val;
    float fval = (float) val;
    int *p = &val;
    show_int(ival);
    show_float(fval);
    show_pointer(p);
}

int main(int argc, char *argv[])
{
    test_show_bytes(12345);

    //float s = 3510593;
    char *s = "abcdef";
    byte_pointer p = (byte_pointer) s;

    show_bytes(p, 6);

	return 0;
}

