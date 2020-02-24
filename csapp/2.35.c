#include <stdio.h>
#include <limits.h>

// Determine whether arguments can be multiplied 
// without overflow.
// set p = x * y, q = p / x, r = p % x;
//
// x * y = p + t * 2^w
// x * y = x * q + r + t * 2^w
// y = q + r / x + t * 2^w / x
//
// so, we can conclude that: 
// while y equals q, if and only if r equals 0 and t equals 0.
int tmult_ok(int x, int y)
{
    int p = x * y;

    return !x || p / x == y;
}

int main(int argc, char* argv[]) {

    int x = INT_MAX/2;
    int y = 2;
    printf("tmult_ok(%d, %d) = %d\n", x, y, tmult_ok(x, y));

}

