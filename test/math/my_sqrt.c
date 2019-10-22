#include <stdio.h>
#include <math.h>

float my_sqrt(float x)
{
	float x0, x1;
	x0 = x / 2;
	x1 = (x0 + x / x0) / 2;

	do  {
		x0 = x1;
		x1 = (x0 + x / x0) / 2;
        printf("x0 = %f0, x1 = %f0, x0 - x1 = %f0 \n", x0, x1, x0 - x1);
	} while (fabs(x0 - x1) > 1e-6);

	return x1;
}

float my_sqrt2(float x)
{
    // float 4Byte, double 8Byte

    // 1. 这里定义g为float时，对90、234求根会进入死循环，用double则不会,
    //      ，原因是浮点数精确度问题，导致 g=(g+x/g)/2 求出的g和原来的g相同
    //      ，即对有些数求根不能精确到小数点后6位
    //      ，只能通过比较x0和x1，来确定是否还能更精确来停止运行
    //
    // 2. 就算是用double类型作为g的类型，是否还会出现死循环的现象？
    //     目前没发现，但不表示不会发生，所以函数my_sqrt()比较保险
    //     double也出现了死循环，对345672进行求根

    double g = x / 2;
    g = (g + x / g) / 2;
    int i = 0;

    while ( i < 50 && fabs(x - g * g) > 1e-20) {
        g = (g + x / g) / 2;
        printf("g = %f0, (x - g*g) = %f0\n", g, fabs(x - g*g));
        ++i; // 防止死循环，最多执行n次
    }
    return g;
}

int main(void)
{
	printf("please input an float number:\n");
	float f;
	scanf("%f", &f);

	printf("my_sqrt(%f) = %f0\n\n", f, my_sqrt(f));

	printf("my_sqrt2(%f) = %f0\n", f, my_sqrt2(f));

	return 0;
}
