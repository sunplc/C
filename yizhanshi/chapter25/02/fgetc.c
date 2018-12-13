#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	FILE *fp;
	fp = fopen("./fgetc.c", "r");
	if (fp == NULL)
		exit(1);

	char c;
	while ((c = fgetc(fp)) != EOF) {
		putchar(c);	
	}
	putchar('\n');
	return 0;
}

