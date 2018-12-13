#include <stdio.h>
#include <string.h>

int main(void)
{
	char str[] = "/usr/local/ /php/bin/php";
	char *delim = "/";
	char *token;
	token = strtok(str, delim);
	printf("%s\n", token);
	//token = strtok(NULL, delim);
	//printf("%s\n", token);

	while ( (token = strtok(NULL, delim)) != NULL) {
		printf("%s\n", token);
	}

	return 0;
}

