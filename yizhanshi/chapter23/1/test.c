#include <stdio.h>

int main(void)
{
	int i = 97;
	int *pi = &i;
	char c = 'a';
	char *pc = &c;
	pc = (char *)pi;
	printf("%d %c\n", *pi , *pc);
	printf("%p %p", pi, pc);
	return 0;
}
