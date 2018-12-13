#include <stdio.h>

#define BUFFSIZ 256

int main(int argc, char *argv[])
{
    char sfile[FILENAME_MAX], tfile[FILENAME_MAX];
    FILE *fp1, *fp2;
    char buff[BUFFSIZ];

    printf("输入源文件名:\n");
    scanf("%s", sfile);
    printf("输入目标文件名:\n");
    scanf("%s", tfile);

    if ( (fp1 = fopen(sfile, "r")) == NULL) {
        printf("无法打开文件: %s", sfile);
        return 0;
    }

    if ( (fp2 = fopen(tfile, "w")) == NULL) {
        printf("无法打开文件: %s", sfile);
        return 0;
    }

    while ( fgets(buff, BUFFSIZ, fp1) )
        fputs(buff, fp2);

    fclose(fp1);
    fclose(fp2);

	return 0;
}

