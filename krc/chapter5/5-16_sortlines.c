#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINES 5000	//能被排序的最大行数
#define MAXLEN 1000		//任一输入行的最大长度

int readlines(char *linestore, int maxstore, char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void quick_sort(char *lineptr[], int left, int right, int (*comp)(void *, void *));
int Getline(char *, int);
int numcmp(const char *s1, const char *s2);
int Strcmp(const char *s, const char *t);
int StrcmpDict(const char *s1, const char *s2);
int CompareChar(const char c1, const char c2);

//使用全局变量保存选项
int numberic = 0, reverse = 0, insensitive = 0, dictionary = 0;

//将输入行按照字母序排序后输出
//不适用内存分配函数，而是在main函数中定义一个数组来存储
//-n 比较两个字符串的前导数值
//-r 使用降序排序
//-f 大小写不敏感
//-d 使用字典序比较字母、数字和空格，其他字符忽略
int main(int argc, char *argv[])
{
	char *lineptr[MAXLINES];	//指向文本行的指针数组
	int maxstore = MAXLINES * MAXLEN;
	char linestore[maxstore];
	int nlines;

	int c;
	while (--argc > 0 && (*++argv)[0] == '-') {
		while ((c = *++argv[0]))
			switch (c){
				case 'n':
					numberic = 1;
					break;
				case 'r':
					reverse = 1;
					break;
				case 'f':
					insensitive = 1;
					break;
				case 'd':
					dictionary = 1;
					break;
				default:
					printf("Invalid option, Usage: ./sortlines -nrfd\n");
					return 1;
					break;
			}
	}
	//printf("n:%d r:%d f:%d d:%d\n", numberic, reverse, insensitive, dictionary);

	if ( (nlines = readlines(linestore, maxstore, lineptr, MAXLINES)) >= 0) {
		if (numberic == 1) {
			quick_sort(lineptr, 0, nlines-1, 
					(int (*)(void *, void *))numcmp);
		} else if (dictionary == 1) {
			quick_sort(lineptr, 0, nlines-1, 
					(int (*)(void *, void *))StrcmpDict);
		} else {
			quick_sort(lineptr, 0, nlines-1, 
					(int (*)(void *, void *))Strcmp);
		}
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
	for (i = 0; i < limit -1 && (c = getchar()) != EOF && c != '\n'; ++i)
		line[i] = c;

	if (c == '\n')
		line[i++] = '\n';

	line[i] = '\0';
	return i;
}

//快速排序
void quick_sort(char *v[], int left, int  right, int (*comp)(void *, void *))
{
	int i, last;
	void swap(char *v[], int i, int j);

	if (left >= right)
		return ;
	swap(v, left, (left + right) / 2);
	last = left;
	for (i = left+1; i <= right; i++)
		if (reverse) {
			if ((*comp)(v[i], v[left]) > 0)
				swap(v, ++last, i);
		} else {
			if ((*comp)(v[i], v[left]) < 0)
				swap(v, ++last, i);
		}
	swap(v, left, last);

	quick_sort(v, left, last-1, comp);
	quick_sort(v, last+1, right, comp);
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

/* 按数值比较s1和s2 */
int numcmp(const char *s1, const char *s2)
{
	double v1, v2;
	v1 = atof(s1);
	v2 = atof(s2);
	//printf("%g %g\n", v1, v2);
	if (v1 > v2) {
		return 1;
	} else if (v1 < v2) {
		return -1;
	} else {
		return 0;
	}
}

int CompareChar(const char c1, const char c2)
{
	printf("%d---\n", insensitive);
	if (insensitive)
		return tolower(c1) == tolower(c2);
	else
		return c1 == c2;
}

//比较两个字符串
int Strcmp(const char *s, const char *t)
{
	for ( ; CompareChar(*s, *t); s++, t++)
		if (*s == '\0')
			return 0;
	if (insensitive)
		return tolower(*s) - tolower(*t);
	else
		return *s - *t;
}

//增加 -d（“字典序”）选项，使程序仅比较字母、数字和空格。
//请确保它可以与 -f协同工作
int StrcmpDict(const char *s1, const char *s2)
{
	while (*s1 != '\0' && *s2 != '\0') {
		if (!(isalnum(*s1) || *s1 == ' '))
			++s1;
		if (!(isalnum(*s2) || *s2 == ' '))
			++s2;

		if (*s1 == '\0' || *s2 == '\0')
			break;
		
		if (CompareChar(*s1, *s2)) {
			printf("%c %c\n", *s1, *s2);
			break;
		} else {
			++s1;
			++s2;
		}
	}

	if (*s1 == '\0')
		return 0;
	else 
		return *s1 - *s2;
}

