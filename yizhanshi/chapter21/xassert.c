/* xassert.c _Assert function */
#include <stdio.h>
#include <stdlib.h>

void _Assert(char *msg)
{
	/* print assertion message and abort */
	fputs(msg, stderr);
	fputs(" -- assertion failed\n", stderr);
	abort();
}
