#include <stdio.h>
#include <string.h>

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

void itoa(int n, char *str)
{
	int i, sign;
	if ( (sign = n) < 0)
		n = -n;
	
	i = 0;
	do {
		str[i++] = n % 10 + '0';
	} while ( (n /= 10) > 0);

	if (sign < 0)
		str[i++] = '-';
	str[i] = '\0';
	
	str_reverse(str);
}

// 将一个数字转换为对应的字符串，与atoi函数相反
int main(void)
{
	//int n = -127;
	int n = -2147483647;
	char str[100];
	itoa(n, str);
	printf("%s\n", str);
	return 0;
}

