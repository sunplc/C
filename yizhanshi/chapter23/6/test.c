#include <stdio.h>

int main(int argc, char *argv[])
{
	int i;
	int *pi = &i;
	int **ppi = &pi;
	int ***pppi = &ppi;
	printf("%p %p %p %p\n", &i, pi, ppi, pppi);
	return 0;
}

