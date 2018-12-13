#include <stdio.h>

int main(void)
{
	int i;
	for (i = 0; i < 10; ++i) {
		printf("i = %d\n", i);
		if (i == 5)
			goto error;
	}
	error:
	{
		printf("mark\n");
		printf("there is.\n");
	}
	return 0;
}
