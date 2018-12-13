#include <stdio.h>

int main(void)
{
	int a = 3, b = 17;
	a = a ^ b;
	b = a ^ b;
	a = a ^ b;
	printf("a=%d, b=%d\n", a, b);
	return 0;
}

