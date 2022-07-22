/*
 * 1. A static function is a function that has a scope that is limited to
 * its object file. 
 *
 * 2.  static global variable is a variable that has a scope that is
 * limited to its object file.
 *
 * 3. a static local variable is a local varible in it's nearest scope, and
 * stored in heap, and will been destroyed until program exit.
 *
 *
 */
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

