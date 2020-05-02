#include <stdio.h>

int div16(int x)
{
    // if x is negative, then right shift x is sign extension,
    // so x >> 31 get 111111...1, otherwise x >> 31 get 000000...0
    int bias = (x >> 31) & ((1 << 4) - 1);
    printf("bias = %d\n", bias);
    return (x + bias) >> 4;
}

int main(int argc, char* argv[])
{
    int x = -33;
    printf("%d / 16 = %d\n", x, div16(x));
}

