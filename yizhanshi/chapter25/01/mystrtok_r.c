#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *mystrtok_r(char *src, char *delim, char **saveptr)
{
	if (src == NULL && *saveptr == NULL)
		return NULL;
	if (src == NULL)
		src = *saveptr;

	char *tmp = src;
	if (*src == '\0') {
		return NULL;
	}
	char c;
	while ( (c = *src) != '\0') {
		if (c == *delim) {
			*src = '\0';	
			++src;
			break;
		} else {
			++src;
		}
	}
	*saveptr = src;
	return tmp;
}

int main(int argc, char *argv[])
{
	if (argc != 4) {
		fprintf(stderr, "Useage: %s string delim subdelim\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	char *src, *src1, *saveptr, *saveptr1;
	char *token, *subtoken;
	int j;
	for (j = 1, src = argv[1]; ; j++, src = NULL) {
		token = mystrtok_r(src, argv[2], &saveptr);	
		if (token == NULL) {
			//printf("token\n");
			break;
		}
		printf("%d: %s\n", j, token);

		for (src1 = token;; src1 = NULL) {
			subtoken = mystrtok_r(src1, argv[3], &saveptr1);	
			//printf(" len = %ld\n", strlen(subtoken));
			if (subtoken == NULL) {
				//printf("subtoken\n");
				break;
			}
			printf(" --> %s\n", subtoken);
		}
	}
	exit(EXIT_SUCCESS);
}
