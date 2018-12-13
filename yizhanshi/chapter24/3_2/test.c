#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	printf("mark\n");
	char **pp = NULL;
	//char *p = "beauty";
	char *p = malloc(20);
	strcpy(p, "what the fuck?");
	pp = &p;
	printf("%s\n", *pp);
	free(p);
	p = NULL;
	return 0;
}

