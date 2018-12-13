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

void itoa(int n, char *str, int min_len)
{
	int i = 0, sign = 0;
	if (n < 0)
		sign = 1;

	do {
		str[i++] = abs(n % 10) + '0';
	} while ( abs(n /= 10) > 0);

	if (sign)
		str[i++] = '-';

	while (i < min_len)
		str[i++] = ' ';
	str[i] = '\0';

	str_reverse(str);
}

// 练习 3-6. 编写函数 itoa 的另一版ᴀ，它接受的参数是三个而不是两个。第三个参数是最小
// 字段宽度；如果必要，转换后的数的左边必须被填充空格以达到足够的宽度。
int main(void)
{
	//int n = 2147483647;
	int n = -2147483648;
	char str[100];
	itoa(n, str, 16);
	printf("%s\n", str);
	return 0;
}

