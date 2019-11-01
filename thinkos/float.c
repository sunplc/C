#include <stdio.h>
#include <stdlib.h>

void binary_print(int x);

union {
    float f;
    unsigned int u;
} p;

// float is 32 bits
// In 32-bit standard, the leftmost bit is the sign bit, s.
// The next 8 bits are exponent, q, and the last 23 bits 
// are the coefficient, c. 
// The value of a floating-point number is : 
//  (-1 ^ s) * c * (2 ^ q)
// 
int main(int argc, char *argv[])
{
    p.f = -13.5;

    // 符号位，指数，系数
    // 二进制的科学计数法表示的整数部分始终是1，所以只需要保存小数部分
    // 指数还需要减去float类型的偏移量127
    unsigned int sign = (p.u >> 31) & 1;
    unsigned int expo = ((p.u >> 23) & 0xff) - 127;
    unsigned int coef = p.u & ((1 << 23) - 1);


    printf("sign = %d\n", sign);
    printf("exponent = %d\n", expo);
    printf("coefficient = 0x%x %d\n", coef, coef);
    binary_print(coef);
    
    coef |= (1 << 23);
    while ((coef & 1) == 0) {
        coef >>= 1;
    }

    printf("coefficient = 0x%x %d\n", coef, coef);
    binary_print(coef);

	return 0;
}

void binary_print(int x)
{
    int len = sizeof(int) * 8;
	int i, arr[len];

	for (i = 0; i < len; i++) {
		if ((x & 0x00000001) == 1)
			arr[i] = 1;
		else
			arr[i] = 0;
		x = x >> 1;
	}

	for (i = len; i > 0; i--) {
		if (i < len && i % 8 == 0)
			putchar(' ');
		printf("%d", arr[i-1]);	
	}

	putchar('\n');
}
