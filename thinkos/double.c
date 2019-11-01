#include <stdio.h>
#include <stdlib.h>

void binary_print(long x);

union {
    double d;
    unsigned long l;
} p;

// double is 64 bits
// In 64-bit standard, the leftmost bit is the sign bit, s.
// The next 11 bits are exponent, q, and the last 52 bits 
// are the coefficient, c. 
// The value of a floating-point number is : 
//  (-1 ^ s) * c * (2 ^ q)
// 
int main(int argc, char *argv[])
{
    p.d = -13.5;

    // 符号位，指数，系数
    // 二进制的科学计数法表示的整数部分始终是1，所以只需要保存小数部分
    // 指数还需要减去double类型的指数偏移量1023
    unsigned int sign = (p.l >> 63) & 1;
    unsigned int expo = ((p.l >> 52) & (0xfff >> 1)) - 1023;
    unsigned long coef = p.l & ((1l << 52) - 1);


    printf("sign = %d\n", sign);
    printf("exponent = %d\n", expo);
    printf("coefficient = 0x%lx\n", coef);
    binary_print(coef);
    
    coef |= (1 << 23);
    while ((coef & 1) == 0) {
        coef >>= 1;
    }

    printf("coefficient = 0x%lx\n", coef);
    binary_print(coef);

	return 0;
}

void binary_print(long x)
{
    int len = sizeof(long) * 8;
	int i, arr[len];

	for (i = 0; i < len; i++) {
		if ((x & 0x00000001l) == 1)
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

