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

// Determine whether arguments can be
// subtracted without overflow.
// WARNING: This code is buggy.
int tsub_ok(int x, int y) {
    return tadd_ok(x, -y);
}

int main(int argc, char* argv[]) {

    int x = INT_MAX, y = -15;

    printf("tsub_ok(%d, %d) = %d\n", x, y, tsub_ok(x, y));

}

