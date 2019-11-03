#include <stdio.h>

void binary_print(int x);

int main(int argc, char *argv[])
{
    unsigned int mask = 0b11011111110111111101111111011111;
    binary_print(mask);

    char str[] = "helloworldsc";

    int i;
    for (i = 0; str[i] != '\0'; i+=4) {
        str[i] &= mask;
        puts(str);
    }

	return 0;
}

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
