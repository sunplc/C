#include <stdio.h>

int main(int argc, char *argv[])
{
	const char c = 'A';
	const char *pc = &c;
	char *pc2 = pc;
	printf("%p\n", pc);
	printf("%p\n", pc2);
	return 0;
}

