#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("Error: too few arguments\n");
		exit(1);
	}

	while (--argc > 0)
		printf("%s%s", *++argv, argc > 1 ? " " : "");
	putchar('\n');
	
	return 0;
}

