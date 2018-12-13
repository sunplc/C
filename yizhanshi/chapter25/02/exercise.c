/* 每隔1秒向文件中写入一条记录
   内容如下：
   1 2017-04-18 04:03:33
   2 2017-04-18 04:03:34
   编号依次增长，下次运行时以追加的方式打开文件，
   继续使用上一条记录的编号
   类似写日志
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

int main(void)
{
	//若文件已append模式打开,则文件的读写位置在文件末尾
	FILE *fp = fopen("test.txt", "a+");
	if (fp == NULL) {
		perror("Open file test.txt");
		exit(1);
	}

	fseek(fp, 0, SEEK_END);
	long posit = ftell(fp);
	//printf(" first position = %ld\n", posit);

	int index = 0;
	if (posit > 2) {
		int j = 0;
		int tmp = posit;
		for (j = 0; j < tmp; j++) {
			posit = ftell(fp);
			if (posit < 2) {
				fseek(fp, 0, SEEK_SET);
				break;
			}
			if (fseek(fp, -2, SEEK_CUR) != 0) {
				perror("fseek file test.txt");
				exit(1);
			} else {
				if (fgetc(fp) == '\n')
					break;
			}
		}

		char *line = malloc(100);
		if (fgets(line, 100, fp) == NULL) {
			perror("fgets error");
			exit(1);
		}
		//puts(line);
		sscanf(line, "%d ", &index);
		free(line);
	}

	++index;
	printf("index:%d\n", index);

	int i;
	for (i = 0; i < 10; i++) {
		sleep(1);
		char buff[30];
		time_t now = time (0);
		strftime (buff, 100, "%Y-%m-%d %H:%M:%S", localtime (&now));
		char rs[100];
		sprintf(rs, "%d %s", index, buff);
		printf ("%s\n", rs);
		fputs(strcat(rs,"\n"), fp);
		fflush(fp); //将缓冲区内容立即写入到文件中
		++index;
	}
	fclose(fp);
	return 0;
}

