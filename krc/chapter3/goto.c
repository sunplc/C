#include <stdio.h>

int main()
{
	goto mark;

	mark:
	printf("mark\n");

	//goto mark; //进入死循环

	return 0;
}

