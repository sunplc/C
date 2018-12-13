#include <stdio.h>
#include <string.h>

#define MAXLINES 5000		//能被排序的最大行数

char *lineptr[MAXLINES];	//指向文本行的指针数组

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void quick_sort(char *lineptr[], int left, int right);

//将输入行按照字母序排序后输出
int main(void)
{
	int nlines;
	if ( (nlines = readlines(lineptr, MAXLINES)) >= 0) {
		quick_sort(lineptr, 0, nlines-1);
		printf(">>>Sorted Result:\n");
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("error: input too big to sort\n");
		return 1;
	}
}

#define MAXLEN 1000		//任一输入行的最大长度
int Getline(char *, int);
char *alloc(int);

//读取输入行
int readlines(char *lineptr[], int maxlines)
{
	int len, nlines;
	char *p, line[MAXLEN];

	nlines = 0;
	while ( (len = Getline(line, MAXLEN)) > 0)
		//字符串数组被写满或无法分配内存时，返回错误
		if (nlines >= maxlines || (p = alloc(len)) == NULL)
			return -1;
		else {
			line[len-1] = '\0';		//删除换行符
			strcpy(p, line);		//将读取的一行复制到分配的内存空间中
			lineptr[nlines++] = p;	//将该内存空间的首地址赋值到字符串数组当前成员
		}
	return nlines;
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

#define ALLOCSIZE 35000		// 可用空间大小

static char allocbuf[ALLOCSIZE];	//用于分配的存储
static char *allocp = allocbuf;		//头一个空闲的位置

// 返回指向n个字符空间的指针
char *alloc(int n)
{
	if (allocbuf + ALLOCSIZE - allocp >= n) {	//满足
		allocp += n;
		return allocp -n;
	} else	//没有足够的空间
		return 0;
}

// 释放p指向的存储
void afree(char  *p)
{
	if (p >= allocbuf && p <  allocbuf + ALLOCSIZE)
		allocp = p;
}


