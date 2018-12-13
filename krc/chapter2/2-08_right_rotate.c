#include <stdio.h>

void print_in_binary(int x);
int right_rotate(int x, int n);

// 练习 2-8. 编写一个函数 right(x,n)，其返回整数 x 向右循环移动 n 位所得到的值。
int main()
{
	int x = 253;
    //print_in_binary(-1);
    //print_in_binary(-2147483648);
	print_in_binary(x);
	x = right_rotate(x, 5);
	print_in_binary(x);
	return 0;
}

int right_rotate(int x, int n)
{
	// 生成掩码mask，最高位为1，其他位为0
	int i, mask = -1 << (sizeof(int) * 8 -1);
	for (i = 0; i < n; ++i)  {
		if ((x & 1) == 1) {
			x >>= 1;
			x |= mask;
		} else {
			x >>= 1;
			x &= ~mask;
		}
	}
	return x;
}


// 将int类型变量按照二进制形式打印出来
void print_in_binary(int x)
{
	int int_bits = sizeof(int) * 8;
	int i, arr[int_bits];
	for (i = 0; i < int_bits; i++) {
		if ((x & 0x00000001) == 1)
			arr[i] = 1;
		else
			arr[i] = 0;
		x >>= 1;
	}
	for (i = int_bits; i > 0; i--) {
		if (i < int_bits && i % 8 == 0)
			putchar(' ');
		printf("%d", arr[i-1]);	
	}
	putchar('\n');
}

