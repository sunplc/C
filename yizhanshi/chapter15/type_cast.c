#include <stdio.h>

int main(void)
{
	//int 和 char 类型转换，char可以直接赋值为整形常量
	//unsigned char c = 'a';
	char c;
	c = 97;
	putchar(c);
	printf("\n(int)c = %d\n", (int)c); // 97
	printf("c == 97 is %d\n", c == 97); // 1

	short s = 0;
	int i = 0;
	printf("s = %d\n", s); // 0
	printf("s == i is %d\n", s==i); // 1

	int in = 3.14;
	printf("in = %d\n", in); // 3
	double d = 3;
	printf("d = %f\n", d + 1); // 4.000000

	int i2 = 0xcffffff3;
	printf("%x\n", 0xcffffff3>>2);
	printf("%x\n", i2>>2);

	return 0;
}
