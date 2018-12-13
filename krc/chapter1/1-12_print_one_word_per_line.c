#include <stdio.h>

#define IN 1
#define OUT 0

/* 练习1-12 把输入的单词打印出来，每行一个 */
int main()
{
    int c, state;
    state = OUT;
    while ( (c = getchar()) != EOF) {
        if (c == '\n' ||  c == '\t' || c == ' ') {
            if (state == IN) {
                state = OUT;
                putchar('\n');
            }
        } else {
            if (state != IN)
                state = IN;
            putchar(c);
        }
    }
    return 0;
}

