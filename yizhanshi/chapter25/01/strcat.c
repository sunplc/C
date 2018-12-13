#include <stdio.h>
#include <string.h>

int main(void)
{
	//char *str1 = "Hello";
	//char *str2 = "World";
	char str1[] = "Hello";
	char str2[] = "World";

	//char *str3 = strcat(str1, str2);
	strcat(str1, str2);
	printf("%s\t%s\n", str1, str2);
	printf("%s\n", strcat(str1, str2));
	printf("%s\n", strncat(str1, str2, 3));
	return 0;
}

