#include <stdio.h>
#define LEN 4

char buf[LEN] = {'a', 'b', 'c', 'd'};

void print_backward(int pos)
{
	if (pos == LEN)
		return;
	print_backward(pos + 1);
	putchar(buf[pos]);
	//print_backward(pos + 1);
}

int main(void)
{
	print_backward(0);
	putchar('\n');
	return 0;
}
