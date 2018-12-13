#include <stdio.h>

// fopen() fclose() -> FILE *fp
// fgetc() fputc()
// fgets() fputs()
// fprintf() fscanf()
// fread() fwrite()
// ftell() fseek() 
// rewind() //将位置指针置为文件首


int main(int argc, char *argv[])
{

    char *filename = "test.txt";
    FILE *fp = fopen(filename, "w+");

    if (fp == NULL) {
        printf("Can't open file %s.", filename);
        return 0;
    }

    int i, n;
    for (i = 1; i <= 10; i++)
        fprintf(fp, "%3d", i);
    for (i = 0; i < 10; i++) {
        fseek(fp, i*3L, SEEK_SET);
        fscanf(fp, "%d", &n);
        fseek(fp, i*3L, SEEK_SET);
        fprintf(fp, "%3d", n+10);
    }
    int rs = 0;
    for (i=1; i<=5; i++) {
        fseek(fp, i*6L, SEEK_SET);
        rs = ftell(fp);
        printf(" -%d- ", rs);
        fscanf(fp, "%d", &n);
        printf("%3d", n);
    }
    putchar('\n');
    fclose(fp);

	return 0;
}

