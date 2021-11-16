#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>

void mmapcopy(int fd, size_t size)
{
    char *rs = (char *) mmap(NULL, size, PROT_READ,
            MAP_PRIVATE, fd, 0);

    //printf("%p\n", rs);
    write(STDOUT_FILENO, rs, size);
}

int main(int argc, char *argv[])
{

    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 0;
    }

    char *filename = argv[1];


    int fd = open(filename, 'r');

    struct stat buf;
    fstat(fd, &buf);
    off_t size = buf.st_size;

    mmapcopy(fd, size);

    return 0;
}
