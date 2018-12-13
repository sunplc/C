#include <stdio.h>

#define LEN 5
int a[LEN] = { 10, 5, 2, 4, 7 };

void print_array()
{
	int i;
	for (i = 0; i < LEN; i++) {
		printf("%d\t", a[i]);	
	}
	putchar('\n');
}

void inserting_sort()
{
	int i, j, tmp = 0;
	int times = 0;
	for (i = 1; i < LEN; i++) {
		print_array();
		tmp = a[i];
		j = i - 1;
		while (j >= 0 && tmp < a[j]) {
			++times;
			a[j+1] = a[j];
			j--;
		}	
		a[j+1] = tmp;	
	}
	
	print_array();
	printf("loop times = %d\n", times);
	return;
}

int main(void)
{
	inserting_sort();
	return 0;
}
