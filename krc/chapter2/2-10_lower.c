#include <stdio.h>

char lower(char c)
{
	// a=97 z=122 A=65 Z=90
	return (c >= 65 || c <= 90) ? c + 32 : c;
}

// 练习 2-10. 重写 lower函数，它将大写字母转换为小写字母，
// 使用一个条件表达式来替代 if-else。
int main()
{
	char c = 'B';
	c = lower(c);
	putchar(c);
	return 0;
}

