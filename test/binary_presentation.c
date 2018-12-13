#include <stdio.h>
#include <limits.h>

#include "functions.c"

int main(int argc, char *argv[])
{
    binary_print(2);
    binary_print(1);
    binary_print(0);
    binary_print(-1);
    binary_print(-2);

    putchar('\n');

    binary_print(INT_MAX);
    binary_print(INT_MAX-1);
    binary_print(INT_MIN+1);
    binary_print(INT_MIN);

	return 0;
}

