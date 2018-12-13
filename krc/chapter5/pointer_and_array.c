#include <stdio.h>

int main(void)
{
	double arr[] = {1.3, 2.4, 3.5, 4.123123};
	//double *pa = arr;
	double *pa = &arr[2];

	//arr++; //错误，不能对数组名进行赋值操作。
	//arr + 1;	//arr+1是正确的

	//float x =  *pa;
	//printf("%f\n", x);

	printf("%lf\n", *arr); 
	printf("%lf\n", *(arr+1));
	printf("\n");

	printf("%f\n", *pa);
	printf("%f\n", pa[-1]);
	printf("%f\n", pa[-2]);
	printf("%f\n", *(pa+1));

	//指针减法
	printf("%d\n", &arr[3] - &arr[0]);
	//指针加法是非法的。没有意义
	//printf("%d\n", &arr[3] + &arr[0]);
	return 0;
}
