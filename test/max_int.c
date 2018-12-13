#include <stdio.h>

#include "functions.c"

int main()
{
	// 八个二进制位表示一个字节，两个十六进制位表示一个字节

    unsigned int a;
	a = 0xffff;
    printf("%u\n", a);
    puts("-------------------------------");

	a = 0xffffffff;
    printf("%d\n", a);
    printf("%u\n", a);
    puts("-------------------------------");

    int i = 2147483647;
    printf("%d\n", i);
    printf("%u\n", i);
    binary_print(i);

    return 0;
}

