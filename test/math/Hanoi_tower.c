#include <stdio.h>

int times = 0;
void move(int n, char a, char b, char c)
{
	if (n == 1) {
		printf("%c -> %c\n", a, c);
		++times;
	} else if (n > 1)  {
		move(n-1, a, c, b);
		printf("%c -> %c\n", a, c);
		++times;
		move(n-1, b, a, c);
	}
}

int main(void)
{
	printf("\ninput number: \n");
	int n;
	scanf("%d", &n);
	if (n  > 30) {
		fprintf(stderr, "number is too large to calculate, it's will spend too much time!\n");
		return 1;
	}
	move(n, 'A', 'B', 'C');
	printf("times = %d\n", times);

	return 0;
}
