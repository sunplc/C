#include <stdio.h>

int get_greatest_common_divisor(int a, int b)
{
	int temp;
	while (1) {
		if (a % b == 0) {
			break;	
		} 
		temp = b;
		b = a % b;
		a = temp;
	}
	return b;
}

int main()
{
	int a = 94, b = 72;
	printf("the greatest common divisor of %d and %d is %d\n", a, b, get_greatest_common_divisor(a, b));
	return 0;
}
