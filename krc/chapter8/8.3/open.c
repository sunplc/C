#include <stdio.h>
#include <fcntl.h>	// open()
#include <unistd.h> // close()

// 访问权限可以指，
// 在UNIX系统中，每个文件对应9比特的权限信息，
// 每个比特分别控制文件所有者、所有者所在组和其他成员对文件的读、写和执行权限
// 因此，通过一个3位的八进制数就可方便的说明不同的权限，例如 755
int main(int argc, char *argv[])
{
	//打开一个文件，若文件不存在则返回-1
	//int fd = open("test.txt", O_RDONLY, 0);

	//打开一个文件，若文件不存在则创建，访问权限为 644
	int fd = open("./1.txt", O_WRONLY | O_CREAT, 0644);
	int n = write(fd, "asdf", 4);
	close(fd);
	printf("fd = %d %d %d\n", fd, n, 0644);

	//创建新文件或覆盖已有的旧文件
	fd = creat("./test.txt", 0);
	printf("fd = %d\n", fd);
	close(fd);
	return 0;
}

