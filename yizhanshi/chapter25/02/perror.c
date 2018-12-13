#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(void)
{
	FILE *fp = fopen("abcde", "r");
	if (fp == NULL) {
		perror("Open file abcde");
		printf("errno: %d\n", errno);
		exit(1);
	}
	return 0;
}

