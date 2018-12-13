#include <stdio.h>

int void_func (int a)
{
	printf("void_func: %d\n", a);
	return 1;
}

int main(int argc, char *argv[])
{
	typedef int I;
	I b = 1, c = 2;
	printf("%d,%d\n", b, c);

	typedef int ARR[3];
	ARR a = {3,4,5};
	printf("%d,%d,%d\n", a[0], a[1], a[2]);

	typedef int F (int);
	F *f;
	f = void_func;
	f(6);

	return 0;
}

