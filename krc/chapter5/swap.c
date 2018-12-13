#include <stdio.h>

void swap(int *pa, int * pb)
{
	int temp = *pa;
	*pa = *pb;
	*pb = temp;
}

int main(void)
{
	int a = 3, b = 13;
	swap(&a, &b);
	printf("a = %d, b = %d\n", a, b);

	int arr[] = {1, 4, 7};
	int *pa = arr;
	printf("arr[0] = %d, pa = %p\n", *pa, pa);
	++pa;
	printf("arr[1] = %d, pa = %p\n", *pa, pa);
	++pa;
	printf("arr[2] = %d, pa = %p\n", *pa, pa);
	return 0;
}

