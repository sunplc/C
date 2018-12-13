#include <stdio.h>

int main(int argc, char *argv[])
{
	char *str = "abcd";
	printf("%p\n", str);
	*str = 'A'; // segmentation fault
	str++;
	printf("%p\n", "asdfas");
	printf("%p\n", "asdfasa");
	printf("%p\n", "asdfasc");
	printf("%ld\n", sizeof("abc"));
	return 0;
}

