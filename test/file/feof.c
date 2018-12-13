#include <stdio.h>

int main(int argc, char *argv[])
{
    FILE *fp = fopen("test.txt", "r+");
    if (fp == NULL)
    {
        printf("Can not open file");
        return 0;
    }

    // EOF 字符等于-1
    // 只有当前文件已经读到过EOF字符，feof函数才会返回值才是非0值
    char c;
    while (1) {
        c = fgetc(fp);
        if (feof(fp))
            break;
        else
            putchar(c);
    }
    fclose(fp);
	return 0;
}

