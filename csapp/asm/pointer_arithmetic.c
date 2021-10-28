#include <stdio.h>

int main()
{
    long E[10];
    int i = 3;

    printf("%p\n", &E[i]);
    printf("%p\n", E);
    printf("%ld\n", &E[i]-E);

}
