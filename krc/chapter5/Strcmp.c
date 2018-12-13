#include <stdio.h>

int Strcmp(char *s, char *t)
{
	int i;
	for (i = 0; s[i] == t[i]; i++)
		if (s[i] == '\0')
			return 0;
	return s[i] - t[i];
}

//指针版本
int Strcmp2(char *s, char *t)
{
	for ( ; *s == *t; s++, t++)
		if (*s == '\0')
			return 0;
	printf("%d %d\n", *s, *t);
	return *s - *t;
}

//strcmp(s, t)，其按照字母序比较字符串 s 和 t，
//并在 s 小于、等于或大于 t 时返回负数、零或者正数。返回值是 s 和 t
//第一个不同的字符相减的差值。
int main(void)
{
	char s[] = "hellooooooooo";
	char t[] = "hello";
	printf("%d\n", Strcmp2(s, t));

	int i;
	for (i = 0; i < 20; i++)
		printf("s[%d]=%c %d, t[%d]=%c %d\n", i, s[i], s[i], i, t[i], t[i]);
	return 0;
}

