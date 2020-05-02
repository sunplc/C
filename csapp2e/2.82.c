/*
 * Value = Y * 2^-k + y * 2^-2k + y * 2^-3k + ...
 * so, Value = Y * (2^-k + 2^-2k + 2^-3k + ...)
 *
 * when i start from 0 to positive infinity
 * and i add one per step, 
 * the ∑2^-ki equals 1/(2^k-1)
 *
 * so, Value = Y * (2^k-1)
 */
#include <stdio.h>

void infinite_string_value(int y, int k)
{
    int denominator = (1 << k) - 1; // 分母
    double d = (double)y / denominator;
    printf("%d/%d approximate %lf\n", y, denominator, d);
}

int main(int argc, char* argv[])
{
    // (a) 101
    // (b) 0110
    // (c) 010011

    int y, k;

    y = 0b100; k = 3;
    infinite_string_value(y, k);

    y = 0b0110; k = 4;
    infinite_string_value(y, k);

    y = 0b010011; k = 6;
    infinite_string_value(y, k);

    return 0;
}

