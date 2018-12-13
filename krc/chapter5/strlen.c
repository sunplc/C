#include <stdio.h>

int Strlen(char *s)
{
	int n = 0;
	for (; *s != '\0'; s++)
		n++;
	return n;
}

//通过指针减法来统计字符串长度 
int Strlen2(char *s)
{
	char *p = s;
	while (*p != '\0')
		p++;
	return p - s;
}

int main()
{
	char str[] = "Hello, world!";
	char *s = "something";
	printf("len = %d\n", Strlen("Hello!"));
	printf("len = %d\n", Strlen2(str));
	printf("len = %d\n", Strlen2(s));
	return 0;
}

