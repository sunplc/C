#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

/* 使用命令 man 2 stat 查看stat函数的介绍 */

int main(void)
{
	struct stat buf;
	stat("/etc/passwd", &buf);
	printf("/etc/passwd file size = %lld\n", (long long int)buf.st_size); // 获取文件大小

	struct stat buf2;
	//int ret = stat("/root/c_exercise/test/stat", &buf2); // stat() 成功时返回0，失败返回-1
	int ret = stat("/root/c_exercise/test/", &buf2); // stat() 成功时返回0，失败返回-1
	printf("is directory %d\n", S_ISDIR(buf2.st_mode)); // 判断是否是目录
	printf("is executable = %d\n", ret == 0 && buf2.st_mode & S_IXUSR ); // 判断文件或目录是否可执行
	return 0;
}

