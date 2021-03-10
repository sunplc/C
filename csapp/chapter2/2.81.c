#include <stdio.h>
#include <limits.h>

/*
 * Not always yields 1, because of Asymmetry of
 * two's complement representation
 */
int A(int x, int y)
{
    return (x < y) == (-x > -y);
}

/* 
 * Always yields 1
 */
int B(int x, int y)
{
    return ((x + y) << 4) + y - x == 17 * y + 15 * x;
    // 16 * x - x + 16 * y + y == 17 * y + 15 * x
    // 15 * x + 17 * y == 17 * y + 15 * x
}

/*
 * Always yields 1
 */
int C(int x, int y)
{
    // for any two's complement integer,
    // ~x + 1 equals -x
    return ~x + ~y + 1 == ~(x + y);
    // ~x + 1 + ~y + 1 == ~(x + y) + 1
    // -x + -y == -(x + y)
    // -x + -y = -x + -y
}

/*
 * Always yeilds 1
 */
int D(int x, int y)
{
    unsigned ux = (unsigned) x;
    unsigned uy = (unsigned) y;

    return (ux - uy) == -(unsigned) (y-x);
    // uy - ux == (unsigned) (y - x);
}

/*
 * Always yields 1
 */
int E(int x)
{
    // for a two's complement integer x, no matter positive
    // or negative number x is, the least significant bit
    // and the second least significant bit alway weights
    // positive 2^0 and 2^1, so after (x >> 2) << 2 operations,
    // x always equals or less than it's former value
    return ((x >> 2) << 2) <= x;
}


int main(int argc, char* argv[])
{
    int x, y;

    // A
    x = INT_MIN, y = 0;
    printf("A() = %d\n", A(x, y));

    // B
    x = INT_MIN / 15;
    printf("B() = %d\n", B(x, y));

    // C
    printf("C() = %d\n", C(x, y));

    // D
    x = INT_MIN, y = INT_MAX;
    printf("D() = %d\n", D(x, y));

    // E
    printf("E() = %d\n", E(INT_MIN));

    return 0;
}

