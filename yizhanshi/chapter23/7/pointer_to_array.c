#include <stdio.h>

int main(int argc, char *argv[])
{
	int a[5] = {0,1,2,3,4};
	int (*pa)[5] = &a;
	printf("%d\n", a[0]);
	printf("%d\n", (*pa)[3]);
	printf("%d\n", (*pa)[4]);

	int arr[5][10] = {{1,2,3,4,5},{6,7}};
	int (*parr)[10] = &arr[0];
	printf("%d\n", parr[1][1]);

	char as[4][3][2] = {{{'a', 'b'}, {'c', 'd'}, {'e', 'f'}},
				   {{'g', 'h'}, {'i', 'j'}, {'k', 'l'}},
				   {{'m', 'n'}, {'o', 'p'}, {'q', 'r'}},
				   {{'s', 't'}, {'u', 'v'}, {'w', 'x'}}};

	char (*pas)[2] = &as[1][0];
	printf("%c\n", pas[5][1]);

	char (*ppas)[3][2] = &as[1];
	printf("%c\n", ppas[1][2][1]);

	return 0;
}

