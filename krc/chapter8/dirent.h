
#ifndef NAME_MAX
#define NAME_MAX 1024		// longest filename component, system-dependent
#endif

typedef struct {
	long ino;
	char name[NAME_MAX+1];	// name + '\0' terminator
} Dirent;

typedef struct {
	int fd;
	Dirent d;
} DIR;

DIR *opendir(char *dirname);
Dirent *readdir(DIR *dfd);
void closedir(DIR *dfd);

#ifndef DIRSIZ
#define DIRSIZ 14
#endif

struct direct {
	ino_t d_ino;
	char d_name[DIRSIZ];
};

/*
int fstat(int fd, struct stat*);


// opendir: open a directory for readdir calls
DIR *opendir(char *dirname)
{
	int fd;
	struct stat stbuf;
	DIR *dp;
	if ( (fd = open(dirname, O_RDONLY, 0)) == -1
		|| fstat(fd, &stbuf) == -1
		|| (stbuf.st_mode & S_IFMT) != S_IFDIR
		|| (dp = (DIR *) malloc(sizeof(DIR))) == NULL)
		return NULL;
	dp->fd = fd;
	return dp;
}
*/

