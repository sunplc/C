/*
 * Value = Y * 2^-k + y * 2^-2k + y * 2^-3k + ...
 * so, Value = Y * (2^-k + 2^-2k + 2^-3k + ...)
 *
 * when i start from 1 to positive infinity
 * and i add one per step, 
 * the ∑2^-ki equals 1/(2^k-1)
 *
 * so, Value = Y / (2^k-1)
 */
#include <stdio.h>

void infinite_binary_string(int y, int k)
{
    int denominator = (1 << k) - 1; // 分母
    double d = (double)y / denominator;
    printf("%d/%d approximate equals %lf\n", y, denominator, d);
}

int main(int argc, char* argv[])
{
    // (a) 101
    // (b) 0110
    // (c) 010011

    int y, k;

    y = 0b0111; k = 4;
    infinite_binary_string(y, k);

    y = 0b0110; k = 4;
    infinite_binary_string(y, k);

    y = 0b01011; k = 5;
    infinite_binary_string(y, k);

    return 0;
}

