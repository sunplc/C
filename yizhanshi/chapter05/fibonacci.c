#include <stdio.h>

int main(void)
{
	int a = 0, b = 1;
	int i, times = 20;
	for (i = 0; i < times; i++) {
		int result = a + b;
		printf("%d ", result);
		if ( i % 2 == 0) {
			a = result;	
		} else {
			b = result;	
		}
	}
	return 0;
}
