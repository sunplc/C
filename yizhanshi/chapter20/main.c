/* main.c */
#include <stdio.h>

//extern void push(char);
//extern char pop(void);
//extern int is_empty(void);

int main(void)
{
	push('a');
	push('b');
	push('c');

	while (!is_empty())
		putchar(pop());

	return 0;
}
