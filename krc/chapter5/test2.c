#include <stdio.h>
#include <ctype.h>
#include <string.h>

//int i;
//i = 100; //错误，不能在main函数外这样声明和初始化
int i = 100;
int insensitive = 0;

int CompareChar(const char c1, const char c2)
{
	printf("%d---\n", insensitive);
	if (insensitive)
		return tolower(c1) == tolower(c2);
	else
		return c1 == c2;
}

//比较两个字符串
int Strcmp(const char *s, const char *t)
{
	for ( ; CompareChar(*s, *t); s++, t++)
		if (*s == '\0')
			return 0;
	if (insensitive)
		return tolower(*s) - tolower(*t);
	else
		return *s - *t;
}

int main(void)
{
	insensitive = 1;
	char *s1 = "how are you";
	char *s2 = "How are you";
	printf("%p %p\n", s1, s2);
	//puts(strcat(s1, s2));
	char *s3 = "cause you've got what i need";
	printf("%d\n", Strcmp(s1, s3));
	
	
	//printf("%c", tolower('H'));
	printf("%c", tolower('0'));
	return 0;
}

