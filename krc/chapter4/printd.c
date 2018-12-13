#include <stdio.h>

//输出整数
void printd(int a)
{
	if (a < 0) {
		putchar('-');
		a = -a;
	}
	if (a / 10)
		printd(a / 10);
	putchar(a % 10 + '0');
}

int main(void)
{
	int a = -65536;
	printd(a);
	return 0;
}

