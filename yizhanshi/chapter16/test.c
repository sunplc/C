/**
 * 测试异或运算是否有先后顺序
 * 即: a ^ b ^ c 是否等于 a ^ c ^ b
 */

#include <stdio.h>

void print_in_binary(unsigned int x);

int main(void)
{
	unsigned int a = 0b00010011, b = 0b00000011, c = 0b00000110, d;
	//d = a ^ c ^ b;
	//d = a ^ b ^ c;
	d = c ^ b ^ a;
	print_in_binary(d);

	a = a ^ b;
	b = a ^ b;
	a = a ^ b;

	print_in_binary(a);
	print_in_binary(b);
	return 0;
}

// 将 unsigned int类型变量按照二进制形式打印出来
void print_in_binary(unsigned int x)
{
	int i, arr[32];
	for (i = 0; i < 32; i++) {
		// if (x & 1) // 判断x的最低位是否是1，即判断x是否是奇数
		if ((x & 0x00000001) == 1)
			arr[i] = 1;
		else
			arr[i] = 0;
		x = x >> 1;
	}
	for (i = 32; i > 0; i--)
		printf("%d", arr[i-1]);	
	putchar('\n');
}
