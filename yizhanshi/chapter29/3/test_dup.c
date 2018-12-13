#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>   // S_IRSUR S_IWUSR

int main(void)
{
    int fd, save_fd;
    char *msg = "This is a test\n";

    fd = open("somefile", O_RDWR|O_CREAT, S_IRUSR|S_IWUSR);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    // dup和dup2函数用于在内核的进程控制块中的文件描述符表中，复制一条记录，
    // 该记录中的文件描述符对应的文件指针的指向和参数oldfd对应的指针地址相同，
    // dup函数返回值是新创建的文件描述符，dup2函数返回值是参数newfd指定的文件描述符的值
    save_fd = dup(STDOUT_FILENO); //新建一个文件描述符，该描述符对应的文件指针的值和STDOUT_FILENO的对应文件指针的值相同，即save_fd 和STDOUT_FILENO都指向标准输出文件结构体
    dup2(fd, STDOUT_FILENO); // 将STDOUT_FILENO对应的文件指针指向fd的指针指向，即此时STDOUT_FILENO对应的文件指针指向之前打开的文件somefile
    close(fd);//关闭文件somefile，因为STDOUT_FILENO仍指向somefile，所以somefile在内核中暂时只会release，不会close
    write(STDOUT_FILENO, msg, strlen(msg));//向STDOUT_FILENO写入内容，会写入到somefile
    dup2(save_fd, STDOUT_FILENO);//将STDOUT_FILENO对应的文件指针指向save_fd的对应文件指针的指向，即指向标准输出
    write(STDOUT_FILENO, msg, strlen(msg));//先STDOUT_FILENO写入内容，会写入到标准输出
    close(save_fd);
	return 0;
}

