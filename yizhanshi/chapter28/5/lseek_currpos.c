#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    off_t currpos;
    // if file not exists.
    int fd = open("1.txt", O_RDONLY); 
    // return -1 when failed, return 0 when success.
    currpos = lseek(fd, 0, SEEK_CUR);
    printf("currpos = %ld\n", currpos);
	return 0;
}

