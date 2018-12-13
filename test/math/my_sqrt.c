#include <stdio.h>
#include <math.h>

float my_sqrt(float a)
{
	float x0, x1;
	x0 = a / 2;
	x1 = (x0 + a / x0) / 2;
	do  {
		x0 = x1;
		x1 = (x0 + a / x0) / 2;
	} while (fabs(x0 - x1) > 1e-6);
	return x1;
}

int main(void)
{
	printf("please input an float number:\n");
	float f;
	scanf("%f", &f);
	printf("my_sqrt(%f) = %f\n", f, my_sqrt(f));
	return 0;
}
