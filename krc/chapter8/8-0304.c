#include <fcntl.h>		// open() creat() O_RDONLY O_WRONLY
#include <unistd.h>		// read() write() lseek()
#include <stdlib.h>		// malloc() free()
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

/*
 * flush the output buffer of a stream
 */
int fflush(FILE *fp)
{
	if (fp->flag._UNBUF || fp->flag._ERR || fp->flag._EOF)
		return EOF;

	int bufsize;
	bufsize = fp->ptr - fp->base;

	if (bufsize > 0)
		if (write(fp->fd, fp->base, bufsize) != bufsize) {
			fp->flag._ERR = 1;
			return EOF;
		}

	fp->ptr = fp->base;
	fp->cnt = BUFSIZ - 1;
	return 0;
}

/*
 * sets the file position of the stream to the given offset
 * return zero if successful, or else it returns a non-zero value.
 */
int fseek(FILE *fp, long offset, int origin)
{
	if (fp->base == NULL)
		return EOF;

	if (!fp->flag._UNBUF && fp->ptr != fp->base) {
		// if is read, trash the buffer
		if (fp->flag._READ) {
			fp->cnt = 0;
			fp->ptr = fp->base;
		// if is write, flush the buffer
		} else if (fp->flag._WRITE) {
			if (fflush(fp))
				return EOF;
		}
	}

	// if failed
	if (lseek(fp->fd, offset, origin) < 0) {
		return EOF;
	// is successful
	} else {
		fp->flag._EOF = fp->flag._ERR = 0;
		return 0;
	}
}

size_t fread(char *str, size_t size, size_t nmemb, FILE *fp)
{
	// if fp can't be read
	if (!fp->flag._READ)
		return 0;

	int total = size * nmemb;
	int c, cnt = 0;
	while (--total > 0) {
		c = getc(fp);
		if (c == EOF)
			break;
		*str++ = c;
		++cnt;
	}
	*str = '\0';
	return (size_t) cnt;
}

size_t fwrite(const char *str, size_t size, size_t nmemb, FILE *fp)
{
	// if fp can not be written
	if (!fp->flag._WRITE)
		return 0;

	int total = size * nmemb;
	int c, cnt = 0;
	while (--total > 0) {
		c = *str++;
		if (c == EOF || c == '\0') {
			break;
		}
		putc(c, fp);
		++cnt;
	}
	fflush(fp);
	return (size_t) cnt;
}

/*
 * close the stream, All buffer are flushed.
 */
int fclose(FILE *fp)
{
	if (!fp->flag._UNBUF && !fp->flag._ERR && !fp->flag._EOF) {
		int bufsize;
		bufsize = fp->ptr - fp->base;

		// if buffer not empty
		if (bufsize > 0)
			if (write(fp->fd, fp->base, bufsize) != bufsize) {
				fp->flag._ERR = 1;
				return EOF;
			}
	}

	fp->flag._READ = fp->flag._WRITE = fp->flag._UNBUF 
		= fp->flag._EOF = fp->flag._ERR = 0;
	free(fp->base);
	fp->base = fp->ptr = NULL;
	fp->fd = 0;
	return 0;
}

int main(int argc, char *argv[])
{
	//复制文件内容到另一个文件
	FILE *fp = fopen("8-02_output.txt", "r");
	int len = 20;
	char str[len];
	int rs = fread(str, 1, len, fp);
	FILE *fp2 = fopen("8-04_output.txt", "w");
	rs = fwrite(str, 1, len, fp2);
	//printf("rs=%d\n", rs);

	fclose(fp);
	fclose(fp2);
//	return 0;

	//从终端获取输入，输出到终端，刷新缓存区
    int c;
    while ((c =getchar()) != 'x') {
        putchar(c);
		//fseek(stdout, 0L, SEEK_SET);
		fflush(stdout);
    }
	fclose(stdout);
	return 0;
}

