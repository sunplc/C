#include <stdio.h>

void binary_print(int x)
{
    int len = sizeof(int) * 8;
	int i, arr[len];

	for (i = 0; i < len; i++) {
		if ((x & 0x00000001) == 1)
			arr[i] = 1;
		else
			arr[i] = 0;
		x = x >> 1;
	}

	for (i = len; i > 0; i--) {
		if (i < len && i % 8 == 0)
			putchar(' ');
		printf("%d", arr[i-1]);	
	}

	putchar('\n');
}

int A(int k)
{
    return -1 << k;
}

int B(int j, int k)
{
    return ~(-1 << k) << j;
}

int main(int argc, char* argv[])
{
    int i = A(10);
    binary_print(i);

    i = B(3, 4);
    binary_print(i);
}

