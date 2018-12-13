#include <stdio.h>

int main(int argc, char *argv[])
{
	int a, b, c, result;
	a = b = c = 0;
	result = -1;
	printf("%d %d %d --- %d\n", a, b, c, result);
	result = scanf("input:%5d %d %2d", &a, &b, &c);
	printf("%d %d %d --- %d\n", a, b, c, result);
	return 0;
}

