#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

#include "getword_with_lineno.h"

//从输入中获取一个单词
//正确地处理下划线、字符串常量、注释、
//以及预处理控制行
int getword(char *word, int maxwordlen, int *lineno)
{
	int i, c, nextc;
	//int len;
	i = c = nextc = 0;
	char temp_word[100];
	char *pword = temp_word;

	nextc = getch();
	while (1) {
		c = nextc;
		nextc = getch();
		if (isspace(c)) {
			if (c == '\n')
				++(*lineno);
			if (i == 0) {
				continue;
			} else {
				ungetch(nextc);
				break;
			}
		}

		if (c == EOF)
			break;

		//以#开头的行是预处理行
		if (c == '#') {
			while (isspace(nextc)) {
				nextc = getch();
				if (nextc == '\n')
					++(*lineno);
			}
			while (isalnum(nextc) ||  nextc == '_') {
				*(pword++) = nextc;
				nextc = getch();
			}
			*pword = '\0';
			//printf("temp_word=%s\n", temp_word);

			//多个预处理行，则略过多行
			//例如：条件包含 #if #ifndef 到 #endif
			if (strcmp(temp_word, "if") == 0 ||
					strcmp(temp_word, "ifndef") == 0) {
				//printf("mark\n");
				pword = temp_word;
				*pword = '\0';
				//先略过当前行
				while ((nextc = getch()) != '\n' && nextc != EOF)
					;
				if (nextc == '\n')
					++(*lineno);
				while (1) {
					//找到#endif行，并略过
					while ((nextc = getch()) != '#' && nextc != EOF) {
						if (nextc == '\n')
							++(*lineno);
					}
					if (nextc == '#') {
						//如果是#字符，获取下一个word判断
						while (isspace(nextc = getch())) {
							if (nextc == '\n')
								++(*lineno);
						}
						while (isalnum(nextc) ||  nextc == '_') {
							*(pword++) = nextc;
							nextc = getch();
						}
						if (nextc == '\n')
							++(*lineno);
						*pword = '\0';
						if (strcmp(pword, "endif")) {
							while ((nextc = getch()) != '\n' && nextc != EOF)
								;
							if (nextc == '\n')
								++(*lineno);
							break;
						}

					} else if (nextc == EOF)
						break;
				}
			// 单个预处理行，例如：#include #define 等等
			} else {
				pword = temp_word;
				*pword = '\0';
				while ((nextc = getch()) != '\n' && nextc != EOF)
					;
			}

		//如果是单行注释，则略过
		} else if (c == '/' && nextc == '/') {
			while ((nextc = getch()) != '\n' && nextc != EOF)
				;
			if (nextc == '\n') {
				nextc = getch();
				continue;
			} else
				break;
			//如果是块注释，则略过
		} else if (c == '/' && nextc == '*') {
			while (1) {
				c = nextc;
				nextc = getch();
				if (c == '*' && nextc == '/')
					break;
				if (nextc == EOF)
					break;
				if (c == '\n')
					++(*lineno);
			}
			if (nextc == EOF)
				break;
			else {
				nextc = getch();
				continue;
			}
		//如果是字符串，则略过
		} else if (c == '"') {
			c = nextc;
			nextc = getch();
			while (!(nextc == '"' && c != '\\')) {
				if (c == '\n')
					++(*lineno);

				if (nextc == EOF)
					break;
				c = nextc;
				nextc = getch();
			}
			break;
		} else if (isalnum(c) || c == '_') {
			if (i < maxwordlen)
				*(word + i++) = c;
			else {
				ungetch(nextc);
				ungetch(c);
				break;
			}
		} else {
			if (c == '\n')
				++(*lineno);
			ungetch(nextc);
			break;
		}
		//printf("c = %c\n", c);
	}

	*(word + i) = '\0';
	if (c != EOF)
		c = *(word + (i - 1));

	//len = (int)strlen(word);
	//if (len > 0)
	//	printf("word = %s\tlen = %d\tc= %c=%d\n",
	//			word, len, c, c);
	//sleep(1);
	return c;
}

#define BUFFSIZE 200
char buff[BUFFSIZE];
int bp = 0;

int getch(void)
{
	if (bp > 0)
		return buff[--bp];
	else
		return getchar();
}

void ungetch(int c)
{
	if (bp < BUFFSIZE)
		buff[bp++] = c;
	else {
		printf("Error: buff overflowed!\n");
		exit(1);
	}
}

void str_reverse(char s[])
{
	int c, i, j, len;
	len = strlen(s);
	for (i = 0, j = len - 1; i < j; ++i, --j) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

void ungets(char *s)
{
	str_reverse(s);
	while (*s != '\0') {
		ungetch(*s);
		s++;
	}
}

