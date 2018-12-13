#include <stdio.h>
#include <string.h>
#include <limits.h> // INT_MIN
#include <stdlib.h> // abs()

void str_reverse(char s[])
{
	int c, i, j, len;
	len = strlen(s);
	for (i = 0, j = len - 1; i < j; ++i, --j) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

void itoa2(int n, char *str)
{
	int i, sign, flag = 0;
	if (n == INT_MIN)
		flag = 1;
	if ( (sign = n) < 0) {
		if (flag)
			n = -(n + 1);
		else
			n = -n;
	}
	
	i = 0;
	do {
		if (i == 0  && flag)
			str[i++] = n % 10 + '0' + 1;
		else
			str[i++] = n % 10 + '0';
	} while ( (n /= 10) > 0);

	if (sign < 0)
		str[i++] = '-';
	str[i] = '\0';
	
	str_reverse(str);
}

void itoa(int n, char *str)
{
	int i = 0, sign = 0;
	if (n < 0)
		sign = 1;

	do {
		str[i++] = abs(n % 10) + '0';
	} while ( abs(n /= 10) > 0);

	if (sign)
		str[i++] = '-';
	str[i] = '\0';

	str_reverse(str);
}

// 练习 3-4. 按照二进制的补码表示法，我们的 itoa 版不能处理最大的负数，即 n
// 的值等于-(2字长-1)。请解释为什么不能。
// 请修改函数，使它无论运行在何种机器上在都能正确地打印该值。
int main(void)
{
	//int n = 2147483647;
	int n = -2147483648;
	char str[100];
	itoa(n, str);
	printf("%s\n", str);
	return 0;
}

