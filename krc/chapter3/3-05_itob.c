#include <stdio.h>	// printf()
#include <string.h>	// strlen()
#include <stdlib.h>	// abs()

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

void itob(int n, char *str, int b)
{
	int i = 0, sign = 0, y;
	if (n < 0)
		sign = 1;
	do {
		y = abs(n % b);
		if (y >= 10) {
			str[i++] = y - 10 + 'a';
		} else {
			str[i++] = y + '0';
		}
	} while ( abs(n /= b) > 0);
	if (sign)
		str[i++] = '-';
	str[i] = '\0';
	str_reverse(str);
}

// 练习 3-5. 编写函数 itob(n, s, b)，它将整数 n 转换为以 b 为底的数所对应的字符表示并
// 放到字符串 s 中。特别地，itob(n, s, 16)将 n 按十六进制数的格式转换到字符串 s中。
int main()
{
	char str[100];
	itob(-7, str, 2);
	printf("%s\n", str);
	itob(255, str, 8);
	printf("%s\n", str);
	itob(-255, str, 16);
	printf("%s\n", str);
	return 0;
}

