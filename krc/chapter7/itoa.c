#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//字符串反转
void str_reverse(char *str)
{
	int c, len;
	len = strlen(str);
	if (len < 1)
		return;

	char *temp;
	for (temp = str + len - 1; str < temp; ++str, --temp) {
		c = *str;
		*str = *temp;
		*temp = c;
	}
}

// int 转 string
char *itoa(int n)
{
	int temp, sign, len = 0;
	if (n < 0) {
		sign = -1;
		// itoa函数无法处理INT_MIN,
		// 因为 -INT_MIN大于int类型的取值范围
		temp = n = -n;
	}
	
	//计算将要生成的字符串长度
	do {
		++len;
	} while ( (temp /= 10) > 0);

	//分配len+1长度的内存,用来存放字符串
	char *p, *str;
	p = str = (char *) malloc(sizeof(len + 1));

	do {
		*(str++) = n % 10 + '0';
	} while ( (n /= 10) > 0);

	if (sign < 0)
		*(str++) = '-';
	*str = '\0';

	//字符串反转
	str_reverse(p);
	return p;
}
