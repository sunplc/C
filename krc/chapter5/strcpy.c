#include <stdio.h>

//数组版本
void Strcpy(char *s, char *t)
{
	int i = 0;
	while ((s[i] = t[i]) != '\0')
		i++;
}

//指针版本
void Strcpy2(char *s, char *t)
{
	while ( (*s++ = *t++) != '\0')
		;
}

int main(void)
{
	char *s, *t;
	//s = "";
	t = "everything is meaningless";
	printf("s=%p, t=%p\n", s, t);
	Strcpy2(s, t);
	puts(s);
	return 0;
}

