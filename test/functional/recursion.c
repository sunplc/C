#include <stdio.h>

int f(int x)
{
    return x <= 1 ? x : x * f(x - 1);
}

int main()
{
    int acc = f(6);
    printf("acc = %d\n", acc);

    return 0;
}
