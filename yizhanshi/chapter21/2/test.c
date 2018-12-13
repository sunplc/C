#include <stdio.h>
#define MAX(a, b) ((a > b) ? (a) : (b))

int main(void)
{
	int a = 3, b = 4;
	int c = MAX(a, b);
	printf("%d\n", c);
	return 0;
}
