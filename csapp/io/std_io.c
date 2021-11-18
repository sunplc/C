#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

void view_file(FILE *fp)
{
    printf("_IO_save_base = %s\n", fp->_IO_save_base);
    printf("_IO_read_base = %s\n", fp->_IO_read_base);
    printf("_IO_read_end = %s\n", fp->_IO_read_end);
    printf("_IO_write_ptr = %s\n", fp->_IO_write_ptr);
    printf("_IO_write_base = %s\n", fp->_IO_write_base);
    printf("_IO_write_end = %s\n", fp->_IO_write_end);
    printf("_IO_buf_base = %s\n", fp->_IO_buf_base);
    printf("_IO_buf_end = %s\n", fp->_IO_buf_end);
}

int main()
{
    char *rstr = (char *)malloc(6);
    char *wstr = "00000";
    ssize_t size;

    FILE *fp = fopen("io.txt", "w+");

    puts(">>>>>>>>>> initial");
    view_file(fp);


    puts(">>>>>>>>>> fwrite");
    fwrite("xxxxx", 5, 1, fp);

    //int a;
    //scanf("%d\n", &a);

    view_file(fp);

    puts(">>>>>>>>>> fwrite");
    fwrite(wstr, 5, 1, fp);
    view_file(fp);



    //puts(">>>>>>>>>> fseek");
    /* fseek(fp, 0, SEEK_SET); */
    //view_file(fp);
    int a;
    scanf("%d", &a);

    puts(">>>>>>>>>> fread");
    size = fread(rstr, 5, 1, fp);
    printf("str = %s, size = %ld\n", rstr, size);
    view_file(fp);

    scanf("%d", &a);

    puts(">>>>>>>>>> fwrite");
    fwrite("yyyyy", 5, 1, fp);
    fwrite("zzzzz", 5, 1, fp);
    view_file(fp);

    puts(">>>>>>>>>> fread");
    size = fread(rstr, 5, 1, fp);
    printf("str = %s, size = %ld\n", rstr, size);
    view_file(fp);


    return 0;
}
