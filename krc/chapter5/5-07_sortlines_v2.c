#include <stdio.h>
#include <string.h>

#define MAXLINES 5000		//能被排序的最大行数
#define MAXLEN 1000		//任一输入行的最大长度

int readlines(char *linestore, int maxstore, char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void quick_sort(char *lineptr[], int left, int right);
int Getline(char *, int);

//将输入行按照字母序排序后输出
//不适用内存分配函数，而是在main函数中定义一个数组来存储
int main(void)
{
	char *lineptr[MAXLINES];	//指向文本行的指针数组
	int maxstore = MAXLINES * MAXLEN;
	char linestore[maxstore];
	int nlines;
	if ( (nlines = readlines(linestore, maxstore, lineptr, MAXLINES)) >= 0) {
		quick_sort(lineptr, 0, nlines-1);
		printf(">>>Sorted Result:%d\n", nlines);
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("error: input too big to sort\n");
		return 1;
	}
}

//读取输入行
//linestore 用于存储所有输出行的字符串
//maxstore linestore的长度
//lineptr 存储每个输入行所在地址的数组
//maxlines lineptr的长度
int readlines(char *linestore, int maxstore, char *lineptr[], int maxlines)
{
	char *p = linestore;
	char line[MAXLEN];
	int len = 0, i = 0;
	while ( (len = Getline(line, MAXLEN)) > 0) {
		if (i >= maxlines || p - linestore > maxstore)
			return -1;
		else {
			line[len-1] = '\0';
			strcpy(p, line);
			lineptr[i++] = p;
			p += len;
		}
	}
	return i;
}

//打印字符串数组
void writelines(char *lineptr[], int nlines)
{
	while (nlines-- > 0)
		printf("%s\n", *lineptr++);
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

//快速排序
void quick_sort(char *v[], int left, int  right)
{
	int i, last;
	void swap(char *v[], int i, int j);

	if (left >= right)
		return ;
	//swap(v, left, (left + right) / 2);
	last = left;
	for (i = left+1; i <= right; i++)
		if (strcmp(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);

	quick_sort(v, left, last-1);
	quick_sort(v, last+1, right);
}

//交换字符串数组的两个元素
void swap(char *v[], int i, int j)
{
	if (i == j) {
		//printf("equal\n");
		return;
	}
	char *temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

