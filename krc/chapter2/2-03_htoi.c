#include <stdio.h>

int my_htoi(char str[]);

// hexadecimal to integer
// 练习2-3. 编写函数htoi(s)，其将一个表示16进制数的字符串（包括可选的0x或0X）转
// 换为对应的整数值。允许出现的数字包括0~9、a~f以及A~F。 
int main()
{
	char str[100];
	// 输入一个十六进制整数
	printf("Input an hex integer number:");
	scanf("%s", str);
	int i = my_htoi(str);
	printf("HEX\t%s\nDEC\t%d\n", str, i);
	return 0;
}

int my_htoi(char str[])
{
	int i = 0, n = 0;
	if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X')) {
		i = 2;
	}
	for ( ; ; ++i) {
		if (str[i] >= '0' && str[i] <= '9') 
			n = 16 * n + str[i] - '0';
		else if (str[i] >= 'a' && str[i] <= 'f') 
			n = 16 * n + str[i] - 'a' + 10;
		else if (str[i] >= 'A' && str[i] <= 'F') 
			n = 16 * n + str[i] - 'A' + 10;
		else
			break;
	}
	return n;
}

