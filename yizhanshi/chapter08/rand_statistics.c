#include <stdio.h>
#include <stdlib.h>
#define N 100000

int a[N];

void gen_random(int upper_bound)
{
	int i;
	for (i = 0; i < N; ++i)
		a[i] = rand() % upper_bound;		
}

int how_many(int value)
{
	int i, count = 0;
	for (i = 0; i < N; ++i)
		if (a[i] == value)
			++count;
	return count;
}

int main(void)
{
	int upper_bound = 10;
	gen_random(upper_bound);
	printf("value\thowmany\n");
	int i;
	for (i = 0; i < upper_bound; ++i)
		printf("%d\t%d\n", i, how_many(i));
	return 0;
}
