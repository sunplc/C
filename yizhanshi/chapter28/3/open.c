#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	int fd = open("somefile", O_WRONLY|O_CREAT, 0664);
	printf("fd = %d\n", fd);
	return 0;
}

