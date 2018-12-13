#include <stdio.h>

int power(int, int);

int main()
{
    printf("%d, %d\n", power(2,10), power(2, 31));
    return 0;
}

int power(int base, int n)
{
    int p;
    for (p = 1; n > 0; --n)
        p = p * base;
    return p;
}
