#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/syscall.h>

#include "syscalls_v2.h"

#define PERMS 0666

FILE *fopen(char *name, char *mode)
{
	int fd;
	FILE *fp;

	if (*mode != 'r' && *mode != 'w' && *mode != 'a')
		return NULL;

	for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
		if (fp->flag._READ == 0 && fp->flag._WRITE == 0)
			break;

	if (fp >= _iob + OPEN_MAX)
		return NULL;

	if (*mode == 'w')
		fd = creat(name, PERMS);
	else if (*mode == 'a') {
		if ((fd = open(name, O_WRONLY, 0)) == -1)
			fd = creat(name, PERMS);
		lseek(fd, 0L, 2);
	} else
		fd = open(name, O_RDONLY, 0);
	
	if (fd == -1)
		return NULL;
		
	fp->fd = fd;
	fp->cnt = 0;
	fp->base = NULL;
	if (*mode == 'r')
		fp->flag._READ = 1;
	else
		fp->flag._WRITE = 1;
	return fp;
}

int _fillbuf(FILE *fp)
{
	int bufsize;
	if (fp->flag._READ == 0 || fp->flag._EOF != 0
			|| fp->flag._ERR != 0)
		return EOF;

	bufsize = (fp->flag._UNBUF) ? 1 : BUFSIZ;

	if (fp->base == NULL)	// no buffer yet
		if ((fp->base = (char *) malloc(bufsize)) == NULL)
			return EOF;		// can't get buffer

	fp->ptr = fp->base;
	fp->cnt = read(fp->fd, fp->ptr, bufsize);

	if (--fp->cnt < 0) {
		if (fp->cnt == -1)
			fp->flag._EOF = 1;
		else
			fp->flag._ERR = 1;
		fp->cnt = 0;
		return EOF;
	}
	return (unsigned char) *fp->ptr++;
}

// 来源：http://www.learntosolveit.com/cprogramming/Ex_8.2.html
int _flushbuf(int c, FILE *f)
{
	int num_written = 0, bufsize;
	unsigned char uc = c;

	//如果f的标识不是可以写入且没有出错或到达文件末尾，则返回EOF
	if (f->flag._WRITE == 0 || f->flag._EOF != 0
			|| f->flag._ERR != 0)
		return EOF;

	// base还没有分配地址，并且flag中没有不缓存标志
	if (f->base == NULL && (f->flag._UNBUF == 0)) {
		// no buffer yet
		if ((f->base =  malloc(BUFSIZ)) == NULL)
			// could not allocate a buffer, so try unbuffered
			f->flag._UNBUF = 1;
		else {
			f->ptr = f->base;
			f->cnt = BUFSIZ - 1;
		}
	}

	if (f->flag._UNBUF) {
		// 如果没有缓冲区，则仅需要将字符uc写入fd
		f->ptr = f->base = NULL;
		f->cnt = 0;
		if (c == EOF)
			return EOF;
		num_written = write(f->fd, &uc, 1);
		bufsize = 1;
	} else {
		// 将缓冲区的内容全部写入fd，然后清空缓冲区
		bufsize = (int)(f->ptr - f->base);
		num_written = write(f->fd, f->ptr, bufsize);
		num_written += write(f->fd, &uc, 1);
		bufsize += 1;
		f->ptr = f->base;
		f->cnt = BUFSIZ - 1;
	}

	if (num_written == bufsize)
		return c;
	else {
		f->flag._ERR = 1;
		return EOF;
	}
}

int main(int argc, char *argv[])
{
	//FILE *fp = fopen("8-02_output.txt", "w");

    int c;
    while ((c =getchar()) != 'x') {
        putchar(c);
    }
	return 0;
}

