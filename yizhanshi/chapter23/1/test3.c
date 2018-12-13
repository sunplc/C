#include <stdio.h>

int *swap(int *px, int *py)
{
	int temp;
	temp = *px;
	*px = *py;
	*py = temp;
	return px
}

int main(void)
{
	int i = 10, j = 20;
	int *p = swap(&i, &j);
	printf("&i = %p, &j = %p\n", &i, &j);
	printf("px = %p\n", p);
	printf("now i = %d, j = %d, *p = %d\n", i, j, *p);
	return 0;
}
