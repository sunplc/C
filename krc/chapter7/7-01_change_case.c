#include <stdio.h>
#include <ctype.h>
#include <string.h>

// 练习 7-1. 编写一个程序，根据程序调用名（放在argv[0]中），
// 实现将大写字母转换为小写字母或将小写字母转换为大写字母的功能。
int main(int argc, char *argv[])
{
	int c, flag = 0;
	if (strcmp(argv[0], "tolower") == 0)
		flag = 1;

	while ((c = getchar()) != EOF) {
		if (flag == 1)
			c = tolower(c);
		else
			c = toupper(c);
		putchar(c);
	}

	return 0;
}

