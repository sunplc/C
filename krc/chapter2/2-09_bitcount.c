#include <stdio.h>

void print_in_binary(int x);
int bitcount(unsigned x);
int bitcount_fast(unsigned x);

// 练习 2-9. 在采用二进制补码的系统中，x &= (x-1) 将 x 中最右边为 1的比特位去掉
// （即置为 0）。请解释原因。利用这一经验编写一个速度更快的 bitcount 版ᴀ。
//
// bitcount函数需要从x的最低位依次检查到x的最高的值为1的位，而bitcount_fast只需要检查x中位值等于1的位，
// 所以bitcount_fast函数更快

int main()
{
	int x = 353;
	print_in_binary(x);
	//x = bitcount(x);
	x = bitcount_fast(x);
	printf("%d\n", x);
	return 0;
}

int bitcount(unsigned x)
{
	int n;
	for (n = 0; x != 0; x >>= 1) {
		//printf("mark\n");
		if (x & 01)
			++n;
	}
	return n;
}

int bitcount_fast(unsigned x)
{
	int n;
	for (n = 0; x != 0; ++n) {
		//printf("mark\n");
		x &= (x - 1);
	}
	return n;
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

