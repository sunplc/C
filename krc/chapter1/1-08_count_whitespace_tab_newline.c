#include <stdio.h>

/* 练习1-8 统计输入中的空格、制表符、换行符个数 */
int main()
{
    int c = 0, w = 0, t = 0, n = 0;
    while ( (c = getchar()) != EOF) {
        if (c == ' ')
            ++w;
        else if (c == '\t')
            ++t;
        else if (c == '\n')
            ++n;
    }
    printf("%d whitespace, %d tab, %d newline\n", w, t, n);
    return 0;
}
