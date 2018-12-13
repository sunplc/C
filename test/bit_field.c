#include <stdio.h>

struct bfield
{
    unsigned f1:1;
    unsigned f2:2;
    unsigned f3:3;
    unsigned f4:2;
};

// 以二进制形式打印 char m
void binary_char(char m)
{
    char arr[8];
    int i;
    for (i=0; i<8; i++) {
        if ((m & 0x01) == 1)
            arr[i] = '1';
        else
            arr[i] = '0';
        m >>= 1;
    }
    for (i=7; i>=0; i--) {
        putchar(arr[i]);
    }
    putchar('\n');
}

int main(int argc, char *argv[])
{
    struct bfield fvar;
    printf("%ld\n", sizeof(fvar));
    fvar.f1 = 1;
    fvar.f2 = 1;
    printf("%u\n", fvar.f1);
    printf("%d\n", fvar.f2);

    unsigned char a, b;
    a = 7 ^ 3;
    b = -4 & 3;
    printf("%d %d\n", a, b);
    
    unsigned char v=  0b10100111;
    unsigned char m = (v+2) ^ (~3);
    binary_char(m);
    printf(">>> %u\n", m);
	return 0;
}

