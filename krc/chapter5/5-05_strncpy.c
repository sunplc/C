#include <stdio.h>

void Strncpy(char *s, char *t, int n)
{
	int i = 0;
	while ('\0' != (*s++ = *t++)) {
		if (i >= n-1) {
			*s = '\0';
			break;
		}
		++i;
	}
}

void Strncat(char *s, char *a, int n)
{
	while (*s != '\0')
		s++;
	int i = 0;
	while (*a != '\0') {
		if (i >= n)
			break;
		*s++ = *a++;
		++i;
	}
	*s = '\0';
}

//指针版本
int Strncmp(char *s, char *t, int n)
{
	int i;
	for (i = 0 ; *s == *t, i < n; s++, t++, i++)
		if (*s == '\0')
			return 0;
	printf("%d %d\n", *s, *t);
	return *s - *t;
}

//练习 5-5. 编写库函数 strncpy、strncat 和strncmp，
//这些函数只处理它们字符串参数的最多前 n 个字符。
//例如，strncpy(s, t, n)将 t 的最多前 n 个字符复制到 s中。它们的全面描述参见附录 B
int main(void)
{
	char s[100]; 
	char *t = "everything is meaningless";

	//printf("s=%p, t=%p\n", s, t);
	Strncpy(s, t, 3);
	puts(s);
	Strncpy(s, t, 5);
	puts(s);

	Strncat(s, t, 10);
	puts(s);
	puts(t);

	printf("Strncmp = %d\n", Strncmp(s, t, 5));

	return 0;
}

