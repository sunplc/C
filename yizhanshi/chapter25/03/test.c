#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	// aoti 识别字符串开头可以被识别为整数的部分
	printf("\natoi\n");
	int i = atoi("123abc");
	printf("%d\n", i);
	i = atoi("    0123abc");
	printf("%d\n", i);
	i = atoi("c123abc");
	printf("%d\n", i);
	
	// atof
	printf("\natof\n");
	float f = atof("3.14abs");
	printf("%f\n", f);

	// strtol
	printf("\nstrtol\n");
	char *endptr;
	i = strtol("123hello", &endptr, 5);
	printf("%d\n", i);
	i = strtol("0x111hello", &endptr, 16);
	printf("%d\n", i);
	printf("%s\n", endptr);
	
	// strtod
	printf("\nstrtod\n");
	f = strtod("3.14+E10abs", NULL);
	printf("%f\n", f);
	return 0;
}

