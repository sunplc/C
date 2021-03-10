#include <stdio.h>

// 使用移位的方法，将int类型变量按照二进制形式打印出来
void binary_print(int x)
{
    int len = sizeof(int) * 8;
	int i, arr[len];

	for (i = 0; i < len; i++) {
		if ((x & 0x00000001) == 1)
			arr[i] = 1;
		else
			arr[i] = 0;
		x = x >> 1;
	}

	for (i = len; i > 0; i--) {
		if (i < len && i % 8 == 0)
			putchar(' ');
		printf("%d", arr[i-1]);	
	}

	putchar('\n');
}

int bis(int x, int y)
{
    return x | y;
}

int bic(int x, int y)
{
    return x & (~y);
}

int bool_or(int x, int y)
{
    return bis(x, y);
}

int bool_and(int x, int y)
{
    return bic(x, bic(0xffffffff, y));
}

int bool_xor(int x, int y)
{
    return bic( bis(x, y), bic(x, bic(0xffffffff, y)) );
}

int main(int argc, char *argv[])
{
    int a = 0b10101101;
    int b = 0b10011001;
    binary_print(a);
    binary_print(b);
    puts("bool_or:");
    binary_print(bool_or(a, b));
    puts("bool_xor:");
    binary_print(bool_xor(a, b));

	return 0;
}

