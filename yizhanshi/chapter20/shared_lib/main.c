/* main.c */
#include <stdio.h>
#include "stack/stack.h"

int a, b = 1;

int main(void)
{
	push('a');
	push('b');
	push('c');
	push('e');

	while (!is_empty())
		putchar(pop());
	putchar('\n');
	
	return 0;
}
