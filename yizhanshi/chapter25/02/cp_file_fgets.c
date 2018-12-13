#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	const char *srcfile = "fseek", *destfile = "b.txt";

	FILE *fpsrc;
	if ( (fpsrc = fopen(srcfile, "r")) == NULL) {
		perror("Open file srcfile");
		exit(1);
	}
	FILE *fpdest;
	if ( (fpdest = fopen(destfile, "w")) == NULL) {
		perror("Open file destfile");
		exit(1);
	}
	int maxletter = 1000;
	char *tmp = (char *)malloc(maxletter);
	while ( fgets(tmp, maxletter, fpsrc) != NULL) {
		fputs(tmp, fpdest);	
	}
	free(tmp);
	return 0;
}
