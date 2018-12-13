#include <stdio.h>

int main(int argc, char *argv[])
{
	int arr[5] = {0,1,2,3,4};
	int *p = arr;
	printf("%d %d\n", arr[3], p[3]);
	
	int a = 5, b = 6, c = 7;
	int *array[3] = {&a, &b, &c};
	int **pa = &array[0];
	//int **pa = array; // Also correct
	printf("%d %d\n", *array[2], *pa[2]);
	printf("%p %p\n", array[2], pa[2]);

	return 0;
}

