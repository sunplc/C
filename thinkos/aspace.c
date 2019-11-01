#include <stdio.h>
#include <stdlib.h>

int global;

void counter()
{
    static int counter;
    counter++;
    printf("address of counter is %p\n", &counter);
}

int main(int argc, char *argv[])
{
    int local = 1;
    int *ptr = malloc(1);

    printf("address of text segment is %p\n", main);
    printf("address of constant segment is %p\n", "hello");
    printf("address of global segment is %p\n", &global);
    printf("address of heap segment is %p\n", ptr);
    printf("address of stack segment is %p\n", &local);
    counter();
	return 0;
}

