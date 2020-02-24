#include <stdio.h>
#include <limits.h>

int main(int argc, char* argv[]) {
    int x = -1;
    unsigned u = 2147483648;

    printf("x = %u = %d\n", x, x);
    printf("u = %u = %d\n", u, u);

    printf("%d\n", -1 > 0U);
    printf("%lu\n", sizeof(int));

    puts("Solution of Practice Problem 2.21:");
    printf("%d\n", -2147483647-1 == 2147483648U);
    printf("%d\n", -2147483647-1 < 2147483647);
    printf("%d\n", -2147483647-1U < 2147483647);
    printf("%d\n", -2147483647-1 < -2147483647);
    printf("%d\n", -2147483647-1U < 2147483647);

    puts("Result of INT_MIN - 1:");
    printf("%d - 1 = %d\n", INT_MIN, INT_MIN - 1);
    puts("Result of INT_MAX + 1:");
    printf("%d + 1 = %d\n", INT_MAX, INT_MAX + 1);
}

