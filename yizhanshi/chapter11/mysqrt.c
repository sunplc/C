#include <stdio.h>

// 使用折半查找的方法,求正实数的平方根
double mysqrt(double n)
{
	// precision 精度
	double precision = 0.000001, start = 0.0, end = n, mid, temp;
	while (start + precision  < end) {
		mid = (start + end ) / 2;
		temp = mid * mid;

		//printf("mid = %f\n", mid);
		if (temp - n <= precision && temp - n >= -precision)
			return mid;
		else if (temp - n > precision)
			end = mid;
		else
			start = mid;
	}
	return mid;
}

int main(void)
{
	printf("please input an positive double number:\n");
	double n;
	scanf("%lf", &n);
	printf("your input number is %f\n", n);
	printf("the sqrt of %f is %f\n", n, mysqrt(n));
	return 0;
}
