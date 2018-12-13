#include <stdio.h>
#define N 3

int arr[N] = {1,2,3};

void arrange(void)
{
	int index = arr[0];
}

int main(void)
{
	int a = 3, b = 9;
	a = a + b;
	b = a - b;
	a = a - b;
	printf("%d %d\n", a, b);
	return 0;
}
