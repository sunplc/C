#include "../csapp.h"

int main()
{
    int n = 6;
    int i;
    for (i = n - 1; i >= 0; i -= 2) {
        Fork();
    }
	printf("hello\n");
	exit(0);
}
