#include <stdio.h>
#include <stdlib.h>

int mycp(const char *srcfile, const char *destfile)
{
	FILE *srcfp;
	if ( (srcfp = fopen(srcfile, "r")) == NULL) {
		perror("Open srcfile error");
		exit(1);
	}
	FILE *destfp;
	if ( (destfp = fopen(destfile, "w")) == NULL) {
		perror("Open destfile error");
		exit(1);
	}
	char ch;
	while ( (ch = fgetc(srcfp)) != EOF)
		fputc(ch, destfp);
	return 1;
}

int main(void)
{
	const char *srcfile = "1.txt";
	const char *destfile = "2.txt";
	int rs = mycp(srcfile, destfile);
	printf("rs = %d\n", rs);
	return 0;
}

