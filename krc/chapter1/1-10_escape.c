#include <stdio.h>

/* 练习 1-10 将输入拷贝到输出，将每个制表符、空格、反斜杠分别替换为\t、\sp、\\ */
int main()
{
    int c;
    while ( (c = getchar()) != EOF) {
        if (c == '\t') {
            printf("\\t");
        } else if (c == ' ') {
            printf("\\sp");
        } else if (c == '\\') {
            printf("\\\\");
        } else {
            putchar(c);
        }
    }
    return 0;
}

