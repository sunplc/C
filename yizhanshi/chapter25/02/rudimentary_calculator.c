#include <stdio.h>

int main(void)
{
	double sum, v;
	sum = 0;
	while (scanf("%lf", &v) == 1)
		printf("\t%.2f\n", sum += v);
	return 0;
}

