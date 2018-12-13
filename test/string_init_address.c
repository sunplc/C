#include <stdio.h>
#include <string.h>

int main()
{
	char *s1 = "hello";
	char s2[] = "hello";

	printf("%d\n", '\0');
	printf("%p\n", s1);
	printf("%p\n", s2);
	printf("%ld\n", strlen(s1));
	printf("%ld\n", strlen(s2));

	return 0;
}

