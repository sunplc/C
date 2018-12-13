#include <stdio.h>
#include <limits.h>	// INT_MIN

#define MAXLEN 100

// itoa函数无法处理INT_MIN,因为 -INT_MIN小于int的取值范围
void itoa(int n, char str[])
{
	static int i = 0;
	if (n < 0) {
		str[i++] = '-';
		n = -n;
	}
	if (n / 10)
		itoa(n / 10, str);
	str[i++] = n % 10 + '0';
}

// 练习 4-12. 运用 printd 的思想编写一个递归版本的 itoa函数；
// 即通过递归调用将一个整数转换为字符串形式。
int main()
{
	int n = INT_MIN + 1;
	//n = -986729;
	char str[MAXLEN];
	itoa(n, str);
	puts(str);
	return 0;
}

