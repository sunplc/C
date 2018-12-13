#include <stdio.h>
#include <ctype.h>

#define IN 1
#define OUT 0

/* 练习 1-11 单词计数程序 */
int main()
{
    int c, nl, nw, nc, state;
    nl = nw = nc = 0;
    state = OUT;

    while ( (c = getchar()) != EOF) {
        ++nc;

        if (c == '\n') {
            ++nl;
        }

        // isblank() 检测字符是否是 空格或制表符\t
        // isspace() 检测字符是否是 空格、\n \r \f \t \v
        if (isspace(c)) {
            state = OUT;
        } else {
            if (state != IN) {
                state = IN;
                ++nw;
            }
        }
    }

    printf("%d lines, %d words, %d characters\n", nl, nw, nc);

    return 0;
}

