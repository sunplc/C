#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int fd = open("test.txt", O_WRONLY | O_CREAT, 0644);
	long pos = lseek(fd, 0, 2);
	printf("pos = %ld\n", pos);
	if (write(fd, "hello", 5) != 5)
		printf("error");
	return 0;
}

