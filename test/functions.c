#include <stdio.h>

// 使用除2的方法，将一个整数以二进制的形式打印出来
void to_binary(unsigned long n)
{
    int r = n % 2;
    if (n >= 2) {
        to_binary(n / 2);
    }
    putchar('0' + r);
}

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

