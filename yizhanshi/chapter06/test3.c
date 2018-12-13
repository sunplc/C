#include <stdio.h>

int main(void)
{
	int i = 0, limit = 100, times = 0;
	int num = 2;
	while (i < limit) {
		int shi = (i % 100 - i % 10) / 10;
		int ge = i % 10;
		//printf("i = %d, shi = %d, ge = %d\n", i, shi, ge);
		if (shi == num)
			times += 1;
		if (ge == num)
			times += 1;
		i++;
	}
	printf("times = %d\n", times);
	return 0;
}
