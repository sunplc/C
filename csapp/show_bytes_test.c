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

int main(int argc, char* argv[])
{
    // Here is very strange, if there is no 'unsigned'

    //typedef unsigned char *bp;
    char c1 = 0xff;
    unsigned char c2 = 0xff;

    printf("%.2x\n", (int)c1);
    printf("%.2x\n", (int)c2);

    int i1 = (int) c1;
    int i2 = (int) c2;
    binary_print(i1);
    binary_print(i2);
}

