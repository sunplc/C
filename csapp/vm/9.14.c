#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>


int main(int argc, char *argv[])
{

    char *filename = "hello.txt";


    int fd = open(filename, O_RDWR);

    struct stat buf;
    fstat(fd, &buf);
    off_t size = buf.st_size;

    char *p = (char *) mmap(NULL, size, PROT_WRITE,
            MAP_SHARED, fd, 0);

    *p = 'J';

    write(STDOUT_FILENO, p, size);

    munmap(p, size);

    return 0;
}
