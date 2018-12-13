#include <stdio.h>
#include <string.h>

void Strcat(char *s, char *a)
{
	while (*s != '\0')
		s++;
	while (*a != '\0')
		*s++ = *a++;
	*s = '\0';
}

int main(void)
{
	//初始化足够的数组长度，防止复制时写过界
	char s[30] = "hello ";
	printf("len=%d\n", (int)strlen(s));
	//printf("s = %p\n", s);
	char a[] = "world 123 0";
	Strcat(s, a);
	puts(s);

	int i;
	for (i = 0; i < 30; i++)
		printf("s[%d]=%c %d\n", i, s[i], s[i]);
	return 0;
}

