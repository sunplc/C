#include <stdio.h>
#include <string.h>

int main(void)
{
	char *haystack = "aihenjiandan";
	char *needle = "an";
	char *rs = strstr(haystack, needle);

	if (rs == NULL) {
		printf("Not found.");
	} else {
		printf("%s\n", rs);
	}

	return 0;
}

