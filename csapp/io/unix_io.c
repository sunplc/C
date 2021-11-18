#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int fd = open("io.txt", O_CREAT|O_RDWR, 
            S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);

    char *str = (char *)malloc(32);
    ssize_t size;
    if ((size = read(fd, str, 5)) >= 0) {
        printf("str == %s \n", str);
        lseek(fd, 5, SEEK_CUR);

    if ((size = read(fd, str, 5)) >= 0) {
        printf("str == %s \n", str);
        }
    }

    return 0;
}
