#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd1, fd2;

    fd1 = open("foo.txt", O_RDONLY, 0);
    close(fd1);
    printf("fd1 = %d\n", fd1);

    fd2 = open("baz.txt", O_RDONLY, 0);
    printf("fd2 = %d\n", fd2);

    return 0;
}
