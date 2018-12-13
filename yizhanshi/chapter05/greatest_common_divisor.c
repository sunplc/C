#include <stdio.h>

int times;
/*
 * Euclid算法：
 * 1.如果a除以b能整除，则最大公约数是b
 * 2.否则，最大公约数等于b和a%b的最大公约数
 */
int get_greatest_common_divisor(int a, int b)
{
	times += 1;
	printf("第%d次, a = %d, b = %d\n", times, a, b);
	if (a % b == 0) {
		return b;	
	} else {
		return get_greatest_common_divisor(b, a % b);	
	}	
}

int main()
{
	int a = 89, b = 144;
	int result = get_greatest_common_divisor(a, b);
	printf("the greatest divisor of %d and %d is %d\n", a, b, result);
	return 0;
}
