#include <stdio.h>
#include <string.h>

int isupper(int c)
{
	return c >= 'A' && c <= 'Z';
}

int Isupper(int c)
{
	return strchr("ABCDEFGHIJKLMNOPQRSTUVWXYZ", c) != NULL;
}

/*
 * 练习 7-9. 诸如 isupper 这样的函数能够以节省空间或节省时间的方式实现。
 * 试探究这两种可能性。
 */
int main(int argc, char *argv[])
{
	int c = 'X';
	printf("result = %d\n", isupper(c));
	printf("result = %d\n", Isupper(c));

	return 0;
}

