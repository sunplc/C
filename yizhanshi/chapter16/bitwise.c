#include <stdio.h>

int countbit(unsigned int x);
void print_in_binary(unsigned int x);
unsigned int multiply(unsigned int x, unsigned int y);

int main(void)
{
	unsigned int i = (0x12345678 >> 8) & ~(~0u << 8);
	//i = i >> 1;
	//i = ~i;
	printf("i = %d\n", i);
	// 检查int类型是否是4个字节32位
	//printf("sizeof(i) = %ld\n", sizeof(i));
	printf("countbit(i) = %d\n", countbit(i));
	print_in_binary(i);

	unsigned int a = 3, b = 7;
	printf("multiply = %d\n", multiply(a, b));
	return 0;
}

// 统计int类型变量中值为1的bit位数
int countbit(unsigned int x)
{
	int i,count = 0;
	for (i = 0; i < 31; i++) {
		if (x % 2 == 1)
			++count;
		x = x >> 1;
	}
	return count;
}

// 将int类型变量按照二进制形式打印出来
void print_in_binary(unsigned int x)
{
	int i, arr[32];
	for (i = 0; i < 32; i++) {
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

// 使用位运算实现简单的整数乘法
unsigned int multiply(unsigned int x, unsigned int y)
{
	unsigned int i, sum = 0;
	for (i = 0; i < 32; i++) {
		if ((y & 0x00000001) == 1)
			sum += x << i;
		y = y >> 1;
	}
	return sum;
}
