#include <stdio.h>

int main(int argc, char *argv[])
{
	int i;
	for (i = 0; i < argc + 1; i++)
		if (argv[i] != NULL)
			printf("argv[%d] = %s\n", i, argv[i]);
		else
			printf("NULL\n");

	return 0;
}

