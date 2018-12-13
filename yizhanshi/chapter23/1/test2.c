#include <stdio.h>

void func(char *pv)
{
	/* *pv = 'A' is illegal */
	*pv = 'A';
	return;

	char *pchar = pv;
	*pchar = 'A';
}

int main(void)
{
	char c;
	func(&c);
	printf("%c\n", c);
	return 0;
}
