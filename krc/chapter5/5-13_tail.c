#include <stdio.h>
#include <string.h>

#define MAXLEN 1000

int my_atoi(char str[])
{
	int i, n = 0;
	for (i = 0; str[i] >= '0' && str[i] <= '9'; ++i) {
		n = 10 * n + (str[i] - '0');
	}
	return n;
}

//获取一行输入并将其保存到line中，保证line以换行符结尾
int Getline(char line[], int limit)
{
	int c, i;
	for (i = 0; i < limit -1 && (c = getchar()) != EOF && c != '\n'; ++i) {
		line[i] = c;
	}
	if (c == '\n') {
		line[i] = '\n';
		++i;
	}
	line[i] = '\0';
	return i;
}

/* 读取输入行
 * linestore 用于存储所有输出行的字符串
 * maxstore linestore的长度
 * lineptr 存储每个输入行所在地址的数组
 * maxlines lineptr的长度
 */
int readlines(char *linestore, int maxstore, char *lineptr[], int maxlines)
{
	char *p = linestore;
	char line[MAXLEN];
	int len = 0, i = 0;
	while ( (len = Getline(line, MAXLEN)) > 0) {
		if (p - linestore > maxstore)
			return -1;
		else {
			line[len-1] = '\0';
			strcpy(p, line);
			lineptr[i % maxlines] = p;
			++i;
			p += len;
		}
	}
	if (i >= maxlines) {
		//最后读入的行
		int last = (i % maxlines == 0) ? (maxlines - 1) : (i % maxlines - 1);
		//printf("last=%d, %s\n", last, lineptr[last]);
		if (last == maxlines - 1)
			return maxlines;
			
		//将lineptr重新排序
		char *tmp[last]; //创建一个临时指针数组
		int j;
		//将lineptr中0~last的元素复制到tmp中
		for (j = 0; j <= last; ++j) {
			tmp[j] = lineptr[j];
		}
		//将lineptr中last+1 ~ maxlines-1的元素移动到lineptr的起始位置
		int k;
		for (k = 0, j = last+1; j < maxlines; ++j, ++k) {
			lineptr[k] = lineptr[j];
		}
		//将tmp中的元素复制到lineptr的尾部
		for (k = 0, j = maxlines - last - 1; j < maxlines; ++j, ++k) {
			lineptr[j] = tmp[k];
		}
		return maxlines;
	} else {
		return i;
	}
}

//打印字符串数组
void writelines(char *lineptr[], int nlines)
{
	while (nlines-- > 0)
		printf("%s\n", *lineptr++);
}

// tail 将标准输入的最后n行打印出来
int main(int argc, char *argv[])
{
	//printf("Usage: tail -n=10\n");
	int i, j = 0, limit = 10;
	for (i = 1; i < argc; i++) {
		if (strlen(argv[i]) >= 4) {
			if (argv[i][j++] == '-' && argv[i][j++] == 'n' 
					&& argv[i][j++] == '=') {
				limit = my_atoi(argv[i] + 3);
			}
		}
	}
	/* printf("limit=%d\n", limit); */
	if (limit <= 0 || limit >= 100) {
		printf("Error: invalid line limit %d!\n", limit);
		return 1;
	}

	char *lineptr[limit];
	int maxstore = limit * MAXLEN;
	char linestore[maxstore];
	int nlines;
	while ( (nlines = readlines(linestore, maxstore, lineptr, limit))) {
		printf("Read %d lines:\n", nlines);
		writelines(lineptr, nlines);
	}
	return 0;
}

