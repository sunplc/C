#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("Error: too few arguments\n");
		exit(1);
	}

	int i;
	for (i = 1; i < argc; i++) {
		printf("%s%s", argv[i], i < argc-1 ? " " : "");
	}
	putchar('\n');
	
	return 0;
}

