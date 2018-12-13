#include <stdio.h>

int ga = 0;

void foo(void)
{
    int a = 0;

    static int sa = 0;

    a += 10;
    sa += 10;
    ga += 10;
    printf("foo2:\t a = %d \t sa = %d \t ga = %d \n", a, sa, ga);
}

int main(int argc, char *argv[])
{
    int i;
    for (i=0; i<10; i++) {
        foo();
    }
	return 0;
}

