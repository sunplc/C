#include <stdio.h>

int main(void)
{
	char c = "hello, world.\n"[2];
	//"world"[0] = c;
	putchar(c);
	putchar('\n');
	char str[] = "hello, world.\n";
	printf("%s", str);
	printf("length = %ld\n", sizeof(str) / sizeof(str[0]));
	char str1[14] = "hello, world.\n";
	printf("length = %ld\n", sizeof(str1)/ sizeof(str1[0]));
	printf("%s", str1);
	return 0;
}
