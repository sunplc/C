#include <stdio.h>

int main(int argc, char *argv[])
{
    char filename[FILENAME_MAX];
    printf("输入文件名:\n");
    scanf("%s", filename);
    FILE *fp = fopen(filename, "r+");

    if (fp == NULL) {
        printf("无法打开文件: %s", filename);
        return 0;
    }

    fseek(fp, 0, SEEK_END);
    printf("文件长度: %ld字节\n", ftell(fp));
    fclose(fp);

	return 0;
}

