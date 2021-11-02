#include <stdio.h>
#include <string.h>
#include <unistd.h>
   
volatile int a = 123;

void test()
{
    char str[] = "hello,world\n";
    printf("%p\n", &str);
    int a = 123;
    printf("%p\n", &a);
}

int main()
{
    printf("%p\n", main);
    printf("%p\n", &a);
    puts("");

    test();

    pause();

    return 0;
}
