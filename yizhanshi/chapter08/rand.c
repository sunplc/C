#include <stdio.h>
#include <stdlib.h>

#define N 20

int a[N];

void get_random(int upper_bound)
{
	int i;
	for (i = 0; i < N; ++i) {
		a[i] = rand() % upper_bound;
	}
}

void print_random()
{
	int i;
	for (i = 0; i < N; ++i) {
		printf("a[%d] = %d\n", i, a[i]);
	}
}

int main(void)
{
	get_random(100);
	print_random();
	return 0;
}
