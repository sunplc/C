#include <stdio.h>
#include "calc.h"

static int sp;
static double stack[MAXVAL];

void push(double f)
{
	if (sp < MAXVAL)
		stack[sp++] = f;
	else
		printf("error: 栈满，不能将%g压栈\n", f);
}

double pop(void)
{
	if (sp > 0) {
		return stack[--sp];
	} else {
		printf("error: 栈空\n");
		return 0.0;
	}
}
