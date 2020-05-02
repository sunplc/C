#include <stdio.h>
#include <limits.h>

// Determine whether arguments can be added without overflow
int uadd_ok(unsigned x, unsigned y) {
    unsigned s = x + y;
    // if did overflow, then s < x and s < y.
    // if didn't overflow, then s > x and s > y.
    printf("s=%u\n", s);
    if (s < x) {
        return 0;
    } else {
        return 1;
    }
}

int main(int argc, char* argv[]) {

    int x = UINT_MAX, y = UINT_MAX;
    y = 0;

    printf("uadd_ok(%u, %u) = %d\n", x, y, uadd_ok(x, y));

}

