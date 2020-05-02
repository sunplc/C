#include <stdio.h>
#include <limits.h>

int tmult_ok(int x, int y)
{
    long long p = ((long long)x) * y;
    return !(p > INT_MAX || p < INT_MIN);
}

int main(int argc, char* argv[]) 
{
    int x = INT_MIN/2;
    int y = 3;
    printf("tmult_ok(%d, %d) = %d\n", x, y, tmult_ok(x, y));
}

