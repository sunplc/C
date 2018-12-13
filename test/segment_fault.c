#include <stdio.h>

//没有给str分配空间，就存储数据
int main(void)
{
	char *str;
	scanf("%s", str);
	puts(str);
	return 0;
}

