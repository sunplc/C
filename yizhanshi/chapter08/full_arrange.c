#include <stdio.h>
#define N 4

int arr[N] = {1,2,3,4};

void print_arr()
{
	int i;
	for (i = 0; i < N; ++i)
		printf("%d ", arr[i]);
	putchar('\n');
}

int main(void)
{
	int i;
	for (i = 0; i < N - 1; ++i) {
		int tmp;
		tmp = arr[i];
		arr[i] = arr[i+1];
		arr[i+1] = tmp;
		print_arr();
	}
	return 0;
}
