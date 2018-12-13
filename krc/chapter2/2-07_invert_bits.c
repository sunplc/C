#include <stdio.h>

void print_in_binary(int x);
int invert_bits(int x, int p, int n);

// 练习 2-7. 编写一个函数 invert(x,p,n)，其将 x 从位置 p 起始的 n
// 个比特位取反（即 1 变为 0，0 变为 1），x 的其余位不变；返回 x。
int main()
{
	int x = 255;
	print_in_binary(x);
	x = invert_bits(x, 5, 4);
	print_in_binary(x);
	return 0;
}

// 位置p从右到左计算，最右边第一个位置记为0；n表示从右向左的n个位
int invert_bits(int x, int p, int n)
{
	// 生成mask掩码，它的最右边的n位为1，其他位都是0
	int mask = 0, i;
	for (i = 0; i < n; ++i) {
		mask <<= 1;
		mask += 1;
	}
	mask <<= p + 1 -n; // 将mask中位值为1的位左移到位置p
	int tmp_mask = x & mask; // 获取x的p位置起n位的值
	tmp_mask = ~tmp_mask; // 将tmp_mask取反
	tmp_mask = tmp_mask & mask; // 将tmp_mask中无关的位重新设置位0
	mask = ~mask;
	x = x & mask; // 将x中需要取反的位设置位0 
	x = x | tmp_mask; // x与y做或运算，即：将x的p位置起的n个位取反
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

