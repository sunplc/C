#include <stdio.h>

int main()
{
    int i = 0;
    puts("input an intger:");
    scanf("%d", &i);
    printf("%d\n", i);
    puts("switch:");

    switch(i) {
        case 1:
            puts("1");
            break;
        case 2:
            puts("5");
            break;
        case 3:
            puts("100");
            break;
        case 4:
            puts("1000");
            break;
        default:
            puts("default");
    }
}
