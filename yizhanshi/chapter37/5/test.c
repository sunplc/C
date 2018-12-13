#include <stdio.h>
#include <stdlib.h> //malloc
#include <string.h> //strcpy
#include <errno.h> // EINTR
#include <unistd.h> // read
#include <fcntl.h> // open

static ssize_t my_read(int fd, char *ptr)
{
	static int read_cnt;
	static char *read_ptr;
	static char read_buf[100];

	if (read_cnt <= 0) {
	again:
		if ( (read_cnt = read(fd, read_buf, sizeof(read_buf))) < 0) {
			if (errno == EINTR)
				goto again;
			return -1;
		} else if (read_cnt == 0)
			return 0;
		read_ptr = read_buf;
	}
	read_cnt--;
	*ptr = *read_ptr++;
	return 1;
}

ssize_t Readline(int fd, void *vptr, size_t maxlen)
{
	ssize_t n, rc;
	char    c, *ptr;

	ptr = vptr;
	for (n = 1; n < maxlen; n++) {
		if ( (rc = my_read(fd, &c)) == 1) {
			*ptr++ = c;
			if (c  == '\n')
				break;
		} else if (rc == 0) {
			*ptr = 0;
			return n - 1;
		} else
			return -1;
	}
	*ptr  = 0;
	return n;
}

int main()
{
	char *s = "hello";
	printf("&s = %p\n", &s);
	printf("s = %s\n", s);
	char *s1;
	s1 = malloc(100);
	printf("sizeof s1=%ld\n", sizeof(s1));
	strcpy(s1, s);
	printf("&s1 = %p\n", &s1);
	printf("s1 = %s\n", s1);
	free(s1);
	return 0;

	// 测试以行读取文件
	char str[1024];
	int n;
	int fd = open("response.txt", O_RDONLY);
	while ( (n = Readline(fd, str, 30)) > 0) {
		printf("header: %s\n", str);
	}
	close(fd);
    return 0;
}

