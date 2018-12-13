#include <stdio.h>

void increment(int *x)
{
	++*x;
}

int main(void)
{
	int i = 3, j = 7;
	increment(&i);
	increment(&j);
	printf("i = %d, j = %d\n", i, j);
	return 0;
}
