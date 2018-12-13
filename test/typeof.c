#include <stdio.h>

int main(int argc, char *argv[])
{
    int a = 3;
    typeof(a) b = 4;
    printf("%d %d\n", a, b);

	return 0;
}

