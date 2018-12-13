#include <stdio.h>

int main(void)
{
	int i, count[5] = {1,2,3,[4]=10,[3]=7};
	for (i = 0; i < 5; ++i) {
		printf("count[%d] = %d\n", i, count[i]);	
	}
	int arr1[5] = {2,3,4,5,6}, arr2[5];
	for (i = 0; i < 5; ++i) {
		arr2[i] = arr1[i];	
	}
	for (i = 0; i < 5; ++i) {
		printf("arr2[%d] = %d\n", i, arr2[i]);	
	}
	printf("%f\n", 15*100.0/17/100);
	return 0;
}
