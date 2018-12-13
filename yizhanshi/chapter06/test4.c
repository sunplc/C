#include <stdio.h>

int main(void)
{
	int a, b, c;
	a = 3;
	b = a++;
	c = a;
	printf("a = %d\n", a);
	printf("b = %d\n", b);
	printf("c = %d\n", c);
	return 0;
}
