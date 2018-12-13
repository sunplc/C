#include <stdio.h>

void print_in_binary(int x);
int setbits(int x, int p, int n, int y);

// 练习 2-6. 编写一个函数 setbits(x,p,n,y)，
// 其将 x 从位置 p 起始的 n个比特位设置为 y 的最右 n 个比特位，
// x 的其余位不变；返回 x。
int main()
{

	int x = 423;
	int y = 31;
	print_in_binary(x);
	print_in_binary(y);
	x = setbits(x, 10, 5, y);
	print_in_binary(x);
	return 0;
}

// 位置p从右到左计算，最右边第一个位置记为0；n表示从右向左的n个位
int setbits(int x, int p, int n, int y)
{
	if  (p + 1 < n)
		return x;

	// 生成mask掩码，它的最右边的n位为1，其他位都是0
	int mask = 0;
	int i;
	for (i = 0; i < n; ++i) {
		mask <<= 1;
		mask += 1;
	}
	y = y & mask; //只保留y的最右边n位
	mask <<= p +  1 -n; // 将mask中位值为1的位左移到位置p
	y <<= p + 1 -n; // 将y中保留的n位有效位也左移到位置p
	mask = ~mask; // mask取反
	x = x & mask; // 将x的从p开始的n个位设置位0
	x = x | y; // x与y做或运算，即：将y的n个位放到x的p位置的n个位中
	return x;
}

// 将int类型变量按照二进制形式打印出来
void print_in_binary(int x)
{
	int i, arr[32];
	for (i = 0; i < 32; i++) {
		if ((x & 0x00000001) == 1)
			arr[i] = 1;
		else
			arr[i] = 0;
		x = x >> 1;
	}
	for (i = 32; i > 0; i--) {
		if (i < 32 && i % 8 == 0)
			putchar(' ');
		printf("%d", arr[i-1]);	
	}
	putchar('\n');
}

