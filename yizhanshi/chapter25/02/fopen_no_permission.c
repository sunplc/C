#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	FILE *fp;
	fp = fopen("abc.txt", "r+");
	if (fp == NULL) {
		// if user is not root, there will be a "Permission denied".
		perror("Open /etc/shadow");
		exit(1);
	}
	fclose(fp);
	return 0;
}

