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

// fun1() performs logical left shift for 3 bytes
// and logical right shift for 3 bytes.
int fun1(unsigned word) {
    return (int) ((word << 24) >> 24);
}

// fun2() performs type cast from unsigned to int, 
// performs logical left shift for 3 bytes 
// and arithmetical right shift for 3 bytes.
int fun2(unsigned word) {
    return ((int) word << 24) >> 24;
}

int main(int argc, char* argv[]) {
    int a,b,c,d;
    a = 0x00000076;
    b = 0x87654321;
    c = 0x000000c9;
    d = 0xEDCBA987;

    int a1,a2,b1,b2,c1,c2,d1,d2;
    a1 = fun1(a);
    a2 = fun2(a);
    b1 = fun1(b);
    b2 = fun2(b);
    c1 = fun1(c);
    c2 = fun2(c);
    d1 = fun1(d);
    d2 = fun2(d);

    printf("\n%.8x:\n", a);
    show_bytes((byte_pointer) &a1, sizeof(int));
    show_bytes((byte_pointer) &a2, sizeof(int));

    printf("\n%.8x:\n", b);
    show_bytes((byte_pointer) &b1, sizeof(int));
    show_bytes((byte_pointer) &b2, sizeof(int));

    printf("\n%.8x:\n", c);
    show_bytes((byte_pointer) &c1, sizeof(int));
    show_bytes((byte_pointer) &c2, sizeof(int));

    printf("\n%.8x:\n", d);
    show_bytes((byte_pointer) &d1, sizeof(int));
    show_bytes((byte_pointer) &d2, sizeof(int));

}

