#include <stdio.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer p, int len) {
    p = p + len - 1;
    printf("0x ");
    while (len-- > 0) {
        printf("%.2X ", *p--);
    }
    printf("\n");
}

int bad_int_size_is_32()
{
    /* Set most significant bit (msb) of 32-bit machine */
    int set_msb = 1 << 31;
    /* Shift pass msb of 32-bit word */
    int beyond_msb = 1 << 16;
    beyond_msb <<= 16;

    /* set_msb is nonzero when word size >= 32.
     * beyond_msb is zero when word size <= 32. */
    return set_msb && !beyond_msb;
}

/* practice B */
int int_size_is_32_B()
{
    int set_msb = 1 << 31;
    show_bytes((byte_pointer) &set_msb,
            sizeof(int));
    int x = set_msb + set_msb - 1;
    return set_msb && !~x;
}

/* practice C */
int int_size_is_32_C()
{
    int set_msb = 1 << 15;
    set_msb <<= 8;
    set_msb <<= 8;
    show_bytes((byte_pointer) &set_msb,
            sizeof(int));
    int x = set_msb + set_msb - 1;
    return set_msb && !~x;
}

/*
 * A: when size of data type int is less than 
 * or equals 32.
 */
int main(int argc, char* argv[])
{
    printf("int_size_is_32_B() = %d\n", int_size_is_32_B());
    printf("int_size_is_32_C() = %d\n", int_size_is_32_C());

    return 0;
}

