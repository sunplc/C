#include <stdio.h>
#include <limits.h>

int main()
{
    short int v = -12345;
    unsigned short u = (unsigned short) v;
    printf("v = %d, u = %u\n", v, u);

    unsigned ui = UINT_MAX;
    int i = (int) ui;
    printf("ui = %u, i = %d\n", ui, i);
}
