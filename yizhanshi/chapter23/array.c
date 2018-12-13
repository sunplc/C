#include <stdio.h>

void print_point(int *p)
{
	printf("%p\n", p);
}
int main(void)
{
	int a[10] = {0,1,2,3,4,5,6,7,8,9};
	print_point(a);
	print_point(&a[0]);
	print_point(&a[1]);
	printf("********\n");
	int *pa = &a[0];
	print_point(pa);
	print_point(&pa[0]);
	print_point(&pa[9]);
	print_point(pa++);
	//pa += 2;
	printf("%d\n", pa[0]);
	printf("%d\n", pa[1]);
	return 0;
}
