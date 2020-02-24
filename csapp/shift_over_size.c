#include <stdio.h>

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

int main(int argc, char *argv[])
{
    int         lval = 0xFEDCBA98 << 32;
    int         aval = 0xFFEDCBA9 >> 36;
    unsigned    uval = 0x00FEDCBA >> 40;

    show_bytes((byte_pointer) &lval, sizeof(int));
    show_bytes((byte_pointer) &aval, sizeof(int));
    show_bytes((byte_pointer) &uval, sizeof(int));

	return 0;
}

