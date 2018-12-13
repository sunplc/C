#include <stdio.h>

int main(void)
{
	int a = 0, b = 1;
	int times = 20, i;
	
	for (i = 0; i < times; i++) {
		if (i % 2 != 0) {
			b = a + b;
			printf("%d ", a);
		} else {
			a =  a + b;
			printf("%d ", b);
		}	
	}
	return 0;
}
