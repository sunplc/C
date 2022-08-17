#include <stdio.h>

int tailF(int x, int acc)
{
    return x <= 0 ? acc : tailF(x - 1, acc * x);
}

int main()
{
    int acc = tailF(6, 1);

    printf("acc = %d\n", acc);

    return 0;
}

