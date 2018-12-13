#include <stdio.h>
#include <string.h>
#include <fcntl.h>		// flags for read and write
#include <sys/types.h>	// typedefs
#define __USE_BSD
#include <sys/stat.h>	// structure returned by stat

//#include "syscalls.h"
#include "dirent.h"

/*
 * istruct stat [> inode information returned by stat <]
 * {
 *     dev_t st_dev; [> device of inode <]
 *     ino_t st_ino; [> inode number <]
 *     short st_mode; [> mode bits <]
 *     short st_nlink; [> number of links to file <]
 *     short st_uid; [> owners user id <]
 *     short st_gid; [> owners group id <]
 *     dev_t st_rdev; [> for special files <]
 *     off_t st_size; [> file size in characters <]
 *     time_t st_atime; [> time last accessed <]
 *     time_t st_mtime; [> time last modified <]
 *     time_t st_ctime; [> time originally created <]
 *     };
 * }
 */

//#define S_IFMT	0160000	// type of file:
//#define S_IFDIR	0040000	// directory
//#define S_IFCHR	0020000	// character special
//#define S_IFBLK	0060000	// block special
//#define S_IFREG	0010000	// regular

void fsize(char *name);
//int stat(char *, struct stat *);
void dirwalk(char *, void (*fcn)(char *));

/* print file name */
int main(int argc, char *argv[])
{
	if (argc == 1)
		fsize(".");
	else
		while (--argc > 0)
			fsize(*++argv);
	return 0;
}

void fsize(char *name)
{
	struct stat stbuf;

	if (stat(name, &stbuf) == -1) {
		fprintf(stderr, "fsize: can't access %s\n", name);
		return;
	}
	if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
		dirwalk(name, fsize);
	else
		printf("%s not a directory\n", name);
	printf("%8ld %s\n", stbuf.st_size, name);
}

#define MAX_PATH 1024

/* dirwalk: apply fcn to all files in dir */
void dirwalk(char *dirname, void (*fcn)(char *))
{
	DIR *dir;
	Dirent *dirent;
	char name[MAX_PATH];

	if ((dir = opendir(dirname)) == NULL) {
		fprintf(stderr, "dirwalk: can't open dir %s\n", dirname);
		return;
	}

	while ((dirent = readdir(dir)) != NULL) {
		// 跳过当前目录和父目录
		if (strcmp(dirent->name, ".") == 0
			|| strcmp(dirent->name, "..") == 0)
			continue;

		if (strlen(dirname) + strlen(dirent->name) + 2 > sizeof(name))
			fprintf(stderr, "dirwalk: name %s %s too long\n",
				dirname, dirent->name);
		else {
			printf("dir = %s, dirent->name = %s\n", dirname, dirent->name);
			sprintf(name, "%s/%s", dirname, dirent->name);
			(*fcn)(name);
		}
	}
	closedir(dir);
}

