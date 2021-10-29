#include <stdio.h>
#include <limits.h>

int main()
{
    int a = INT_MAX;
    int b = INT_MIN;
    printf("%d %d, %d, %d\n", a, b, a+b, b-a);
}
