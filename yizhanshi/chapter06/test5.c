#include <stdio.h>

is_prime(int n)
{
	int i;
	for (i = 2; i < n; ++i) {
		if (n % i == 0)
			break;
	}
	if (i == n)
		return 1;
	else
		return 0;
}

int main(void)
{
	int i, limit = 100;
	for (i = 0; i < limit; ++i) {
		if (!is_prime(i))
			continue;
		printf("%d ", i);
	}
	putchar('\n');	
	int j = 0;
	for (j = 0; j < 10; j++) {
		printf("j = %d\n", j);	
		if(j == 3)
			break;
	}
	printf(">>> j = %d\n", j);	
	return 0;
}
