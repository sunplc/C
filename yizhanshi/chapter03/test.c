#include <stdio.h>

void increment(int a);

int main(void)
{
	int i = 1, j = 2;
	increment(i);
	increment(j);
	printf("i = %d\n", i);
	printf("j = %d\n", j);
}

void increment(int a)
{
	a = a + 1;
	printf("value is %d\n", a);
}
