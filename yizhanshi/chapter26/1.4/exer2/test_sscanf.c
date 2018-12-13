#include <stdio.h>

int main(void)
{
    char str[] = "2017-05-21 21:52:11";
    int a, b, c, d, e, f;
    sscanf(str, "%d-%d-%d %d:%d:%d", &a, &b, &c, &d, &e, &f);
    printf("%d %d %d %d %d %d\n", a, b, c, d, e, f);
}
