#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h> //open close
#include <sys/stat.h> //stat() S_ISDIR S_IXUSR

#include "wrap.h"

#define MAXLINE 10240 //设置读取的行的最大字符数
#define SERV_PORT 8080 // HTTP端口

int main()
{
    struct sockaddr_in servaddr, cliaddr;
    socklen_t cliaddr_len;
    int listenfd, connfd;
    char buf[MAXLINE];
    char str[INET_ADDRSTRLEN];
	char *token, *method, *uri, *protocol, *saveptr;
    int  i, j, n;

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

	// 设置tcp连接关闭时关闭socket描述符，以便立即重启服务。 ？
	int opt = 1;
	setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    Bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    Listen(listenfd, 20);
    printf("\nAccepting connections ...\n");

    while (1) {
        cliaddr_len = sizeof(cliaddr);
		// 接受tcp连接
        connfd = Accept(listenfd,
                (struct sockaddr *)&cliaddr, &cliaddr_len);

		printf("Received request from %s at port %d\n",
				inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)),
				ntohs(cliaddr.sin_port));

		// 以行为单位读取请求
		for (i = 0; i < 100 ;i++) {
			n = Readline(connfd, buf, MAXLINE);
			if (n == 0) {
				printf("Read HTTP request over.\n");
				break;
			}
			// 空行(内容为/r/n) 表示http请求头结束，暂时只读取请求头
			if (n == 2 && buf[0] == '\r' && buf[1] == '\n')
				break;
			
			printf("Request header: %s", buf);

			// 读取http请求头第一行，获取相关数据
			if (i == 0) {
				method = malloc(100);
				uri = malloc(100);
				protocol = malloc(100);

				char *strbuf = (char *)buf;
				for (j = 0; j <= 2; j++, strbuf = NULL) {
					token = strtok_r(strbuf, " ", &saveptr);
					//printf("token=%s\n", token);
					if (token == NULL) {
						break;
					}
					if (j == 0)
						strncpy(method, token, 99);
					else if (j == 1)
						strncpy(uri, token, 99);
					else if (j == 2)
						strncpy(protocol, token, 99);
				}
			}

		}
		printf("\nmethod = %s, uri = %s, protocol = %s",
				method, uri, protocol);
		free(method);
		free(protocol);
		
		// 如果请求的是根目录，返回索引文件
		if (uri[0] == '/' && uri[1] == '\0') {
			char *urifile = "./html/index.html";
			strcpy(uri, urifile);
		} else {
			char *wwwroot = malloc(200);
			strcpy(wwwroot, "./html");	
			strcat(wwwroot, uri);
			strcpy(uri, wwwroot);
			free(wwwroot);
		}
		printf("uri = %s\n", uri);
		
		// 判断请求的文件是否存在
		if (access(uri, F_OK) != -1) { 
			// 响应 200
			Write(connfd, "HTTP/1.1 200 OK\r\n", 17);
			Write(connfd, "Content-type: text/html\r\n", 25);
			Write(connfd, "\r\n", 2);

			// 判断文件是否是 可打开的文件，并且不是目录，并且是有可执行权限的
			struct stat filebuf;
			if (stat(uri, &filebuf) == 0 && 
					!S_ISDIR(filebuf.st_mode) &&
					filebuf.st_mode & S_IXUSR) {

				// 执行CGI程序
				// 创建子进程，使用dup2将子进程的标准输出重定向到connfd
				// 在子进程中执行该可执行文件
				pid_t pid = fork();
				if (pid == 0) {
					dup2(connfd, STDOUT_FILENO);
					execl(uri, "nothing", NULL);
				}
			
			} else {
				// 打开uri文件，读取内容作为http响应body
				int fd = open(uri, O_RDONLY);
				if (fd < 0)
					perr_exit("open uri file");

				while ( (n = Readline(fd, buf, MAXLINE)) > 0) {
					Write(connfd, buf, n);
				}
				Close(fd);
			}
		} else {

			// 打开404.txt，读取内容作为http响应内容
			int fd = open("404.txt", O_RDONLY);
			if (fd < 0)
				perr_exit("open 404.txt");

			while ( (n = Readline(fd, buf, MAXLINE)) > 0) {
				Write(connfd, buf, n);
			}
			Close(fd);
		}
		free(uri);

		// 关闭tcp连接
        Close(connfd);
		printf("Connection closed.\n\n");
    }
    return 0;
}

