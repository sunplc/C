#include <stdio.h>

// fopen() fclose() -> FILE *fp
// fgetc() fputc()
// fgets() fputs()
// fprintf() fscanf()
// fread() fwrite()
// ftell() fseek() 
// rewind() //将位置指针置为文件首

int i = 123;

int main(int argc, char *argv[])
{
    printf("&i = %p\n", &i);

    printf("io buffer size = %d\n", _IO_BUFSIZ);

    char *filename = "test.txt";
    FILE *fp = fopen(filename, "r+");
    printf("fp = %p\n", fp);

    if (fp == NULL) {
        printf("Can't open file %s.", filename);
        return 0;
    }

    // 位置从0开始计算
    printf("position = %ld\n", ftell(fp));

    char c;
    while ((c = fgetc(fp)) != EOF) {
        //putc(c, fp);
        printf("position = %ld\n", ftell(fp));
    }
    fclose(fp);

	return 0;
}

