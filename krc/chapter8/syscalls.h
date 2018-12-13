#ifdef BUFSIZ
#undef BUFSIZ
#endif

#ifdef NULL
#undef NULL
#endif

#define	NULL	0
#define	EOF		(-1)
#define BUFSIZ	1024
#define OPEN_MAX 20

typedef struct _iobuf {
	int cnt;	// character left
	char *ptr;	// next character position
	char *base;	// location of buffer
	int flag;	// mode of file access
	int fd;		// file descriptor
} FILE;

extern FILE _iob[OPEN_MAX];

#define stdin	(&_iob[0])
#define stdout	(&_iob[1])
#define stderr	(&_iob[2])

enum _flags {
	_READ	=	01,	// file open for reading, binary 1
	_WRITE	=	02,	// file open for writing, binary 10
	// _UNBUF等于4会导致输出进入缓存区而无输出
	_UNBUF	=	04,	// file is unbuffered
	//_UNBUF	=	03,	// file is unbuffered, binary 11
	_EOF	=	010,// EOF has occurred, binary 1000
	_ERR	=	020	// error has occurred, binary 10000
};

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#define feof(p)		(((p)->flag & _EOF) != 0)
#define ferror(p)	(((p)->flag & _ERR) != 0)
#define fileno(p)	((p)->fd)

#define getc(p)		(--(p)->cnt >= 0 \
			? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define putc(x,p)	(--(p)->cnt >= 0 \
			? *(p)->ptr++ = (x) : _flushbuf((x),p))

#define getchar()	getc(stdin)
#define putchar(x)	putc((x), stdout)

FILE _iob[OPEN_MAX] = {
	{0, (char *) 0, (char *) 0, _READ, 0},
	{0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 1}, //设置stdout不缓存
	{0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2}
};

