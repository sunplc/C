#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

int gettoken(void);
int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];
int getch(void);
void ungetch(int c);
void ungets(char *s);
void str_reverse(char s[]);
int getnexttoken(void);

// 练习 5-19. 修改 undcl 使其不会增加冗余的圆括号到声明中。
int main(int argc, char *argv[])
{
	int type, nexttype;
	char temp[MAXTOKEN];

	while (gettoken() != EOF) {
		strcpy(out, token);
		while ((type = gettoken()) != '\n') {

			if (type == PARENS || type == BRACKETS)
				strcat(out, token);
			else if (type == '*') {
				//如果*号后面是圆括号或方括号(即函数或数组)，
				//则需要在*号外用括号括起来，否则不用括起来
				nexttype = getnexttoken();
				if (nexttype == PARENS || nexttype == BRACKETS)
					sprintf(temp, "(*%s)", out);
				else
					sprintf(temp, "*%s", out);
				strcpy(out, temp);
			} else if (type == NAME) {
				sprintf(temp, "%s %s", token, out);
				strcpy(out, temp);
			} else
				printf("Invalid input at %s\n", token);
		}
		printf("%s\n", out);
	}
	return 0;
}

/* gettoken 返回下一个标记
 * 跳过空格和制表符，找到下一个标记；
 * 标记可以是名字、一对圆括号、一对方括号（可能包含数字），
 * 或者其他任意单个字符 */
int gettoken(void)
{
	int c;
	char *p = token;

	while ((c = getch()) == ' ' || c == '\t')
		;
	if (c == '(') {
		if ((c = getch()) == ')') {
			strcpy(token, "()");
			return tokentype = PARENS;
		} else {
			ungetch(c);
			return tokentype = '(';
		}
	} else if (c == '[') {
		for (*p++ = c; (*p++ = getch()) != ']'; )
			;
		*p = '\0';
		return tokentype = BRACKETS;
	} else if (isalpha(c)) {
		for (*p++ = c; isalnum(c = getch()); )
			*p++ = c;
		*p = '\0';
		ungetch(c);
		return tokentype = NAME;
	} else {
		*p++ = c;
		*p = '\0';
		return tokentype = c;
	}
}

//获取下一个token和tokentype，
//然后将token放回输入缓存buff中
int getnexttoken(void)
{
	char prevtoken[MAXTOKEN];
	int nexttype;
	strcpy(prevtoken, token);
	nexttype = gettoken();
	//printf("next=%s\n", token);
	ungets(token);
	strcpy(token, prevtoken);
	return nexttype;
}

#define BUFFSIZE 100
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

