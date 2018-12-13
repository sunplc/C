#include <stdio.h>

int main(void)
{
	char c;
	while ( (c = getchar()) != EOF) {
		printf("%d\n", c);	
	}
	return 0;
}

