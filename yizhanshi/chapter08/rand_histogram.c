#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 100000
#define UPPER_BOUND 10

int a[N];

void gen_random()
{
	int i;
	for (i = 0; i < N; ++i)
		a[i] = rand() % UPPER_BOUND;		
}

int main(void)
{
	srand(time(NULL));
	gen_random(UPPER_BOUND);

	printf("value\thowmany\n");
	int histogram[UPPER_BOUND] = {0};
	int i;
	for (i = 0; i < N; ++i)
		histogram[a[i]]++;

	for (i = 0; i < UPPER_BOUND; ++i)
		printf("%d\t%d\n", i, histogram[i]); 
	putchar('\n');

	int max = 0, min = 0;
	for (i = 0; i < UPPER_BOUND; ++i) {
		if (histogram[i] > max)
			max = histogram[i];
		if (i == 0)
			min = histogram[i];
		else if (histogram[i] < min)
			min = histogram[i];
	}
	printf("the min is %d, the max is %d\n", min, max);
	
	putchar('\n');
	printf("mount\t");
	for (i = 0; i < UPPER_BOUND; ++i)
		printf("%d\t", i); 
	putchar('\n');

	int hierarchy = 10;
	int step = N / UPPER_BOUND / hierarchy;
	int j;
	for (j = 0; j < hierarchy + ((max - N / UPPER_BOUND) / step + 1); ++j) {
		int level = (j + 1) * step;
		printf("%d\t", level);
		for (i = 0; i < UPPER_BOUND; ++i)
			if (histogram[i] >= level)
				printf("*\t");
			else
				printf(" \t");
		putchar('\n');
	}
	putchar('\n');
		
	return 0;
}
