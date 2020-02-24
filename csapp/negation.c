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

    // In Two's Complement representation,
    // -x = 2^w - x, 
    // this is equivalent to: 
    // -x = ~x + 1.

    int x = INT_MIN;
    int y = -x;

    show_bytes((byte_pointer) &x, sizeof(int));
    show_bytes((byte_pointer) &y, sizeof(int));
    printf("x = %d, y = %d, x + y = %d\n",
            x, y, x + y);

    x = -12345;
    y = -x;
    show_bytes((byte_pointer) &x, sizeof(int));
    show_bytes((byte_pointer) &y, sizeof(int));
    printf("x = %d, y = %d, x + y = %d\n",
            x, y, x + y);
}

