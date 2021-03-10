#include <stdio.h>
#include <limits.h>

// Determine whether arguments can be added without overflow
int tadd_ok(int x, int y) {
    int s = x + y;
    printf("sum = %d\n", s);

    if (x < 0 && y < 0 && s >= 0) {
        return 0;
    } else if (x > 0 && y > 0 && s < 0) {
        return 0;
    }

    return 1;
}

// This code is buggy.
// Because it will always return 1 for any cases,
// even if for positive overflow or negative overflow.
int tadd_ok_buggy(int x, int y) {
    int sum = x+y;
    return (sum-x == y) && (sum-y == x);
}

int main(int argc, char* argv[]) {

    int x = INT_MIN, y = INT_MIN;

    printf("tadd_ok(%d, %d) = %d\n", x, y, tadd_ok(x, y));
    printf("tadd_ok_buggy(%d, %d) = %d\n", x, y, tadd_ok_buggy(x, y));

}

