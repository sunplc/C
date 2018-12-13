/* main.c */
#include <stdio.h>
#include "stack.h"

//void push(char);
//char pop(void);
//int is_empty(void);
//extern int top;

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
