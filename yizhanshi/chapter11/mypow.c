#include <stdio.h>
#include <math.h>

// 使用循环相乘的方法,求正整数n次方
long mypow(int number, int n)
{
	long product = 1;
	int i;
	for (i = 0; i < n; i++) {
		product *= number;
		printf("%ld\n", product);
	}
	return product;
}

// 为了更快计算,用乘积结果再相乘n1次,再乘以number乘n2次
long mypow1(int number, int n)
{
	int n1, n2, temp = 1;
	for (n1 = 0; n1 < n; n1++) {
		temp *= 2;	
		if(temp > n)
			break;
	}
	
	long product;
	if (n1 > 0) {
		n2 = n - pow(2, n1);
		product = number;
	} else {
		n2 = n;
		product = 1;
	}
	//printf("%d %d\n", n1, n2);

	int i;
	for (i = 0; i < n1; i++) {
		product *= product;
		printf("%ld\n", product);
	}
	for (i = 0; i < n2; i++) {
		product *= number;
		printf("%ld\n", product);
	}
	return product;
}

int main(void)
{
	int number = 2, n = 19;
	long product = mypow(number, n);
	printf("%d^%d = %ld\n", number, n, product);

	product = mypow1(number, n);
	printf("%d^%d = %ld\n", number, n, product);
	return 0;
}
