#include <stdio.h>

int bar(int a, int b)
{
	int e = a + b;
	return e;
}

int foo(int a, int b)
{
	return bar(a, b);
}

int main(void)
{
	foo(2, 3);
	return 0;
}
