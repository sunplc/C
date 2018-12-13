#include <stdio.h>

int main(void)
{
	int i = 0;
	unsigned int sum = 0;
	for (; i < 16; i++) {
		sum += 1U << i;
		printf("i = %d\n", i);
	}
	printf("i = %d\n", i);
	printf("0x%x\n", sum);
	return 0;
}
