#include <stdio.h>

int main(void)
{
	//int a[][2] = {{1,2},{3,4},{5,6}};
	int a[3][2] = {[0][1]=34, [2][1]=7, [1][0]=5};
	//printf("%d\n", a[6]);
	int i, j;
	for (i = 0; i < 3; ++i) {
		for (j = 0; j < 2; ++j)
			printf("%d ", a[i][j]);
		putchar('\n');
	}

	struct complex_struct {
		double x, y;	
	} point[4] = { [1].x = 3.141592};

	printf("%f\n", point[1].x);

	struct {
		double x, y;
		int count[4];
	} s = { .count[1] = 7 };	

	printf("%d\n", s.count[1]);
	

	return 0;
}
