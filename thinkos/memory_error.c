#include <stdio.h>

void f1()
{
    int i, array[100];
    for (i = 0; i < 100; i++) {
        array[i] = -i;
    }
}

void f2()
{
    int x = 17;
    int arr[10];
    int y = 123;

    printf("arr[-1] = %d\n", arr[-1]);
    printf("arr[-2] = %d\n", arr[-2]);
    printf("arr[10] = %d\n", arr[10]);
    printf("arr[11] = %d\n", arr[11]);
}

int main(int argc, char *argv[])
{

    f1();
    f2();
	return 0;
}

