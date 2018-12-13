#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

void dcl(void);
void dirdcl(void);

int gettoken(void);
int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];
int getch(void);
void ungetch(int c);

// 练习 5-20. 扩展dcl，使其可以处理
// 包括函数参数类型、const等限定符等等的声明
int main(int argc, char *argv[]) {
	while (gettoken() != EOF) { //输入行的第一个标记是数据类型
		if (*token == '#') { //如果是#开头的行，则跳过
			while ( getch() != '\n')
				;
			continue;
		} else {
			strcpy(datatype, token);
		}
		out[0] = '\0';
		dcl();	//解析输入行的剩余部分
		if (tokentype != '\n') {	//语法错误
			//printf("syntax error, tokentype=%c\n", tokentype); 
			while ( getch() != '\n') //若行尾有其他字符，则跳过
				;
		}
		printf("%s: %s %s\n", name, out, datatype);
	}
	return 0;
}

//解析一个声明
void dcl(void)
{
	int ns;
	for (ns = 0; gettoken() == '*'; )
		ns++;
	dirdcl();
	while (ns-- > 0)
		strcat(out, " pointer to");
}

//解析一个直接声明
void dirdcl(void)
{
	if (tokentype == '(') {		// (dcl)
		dcl();
		if (tokentype != ')')
			printf("error: missinig )\n");
	} else if (tokentype == NAME) { //变量名字
		strcpy(name, token);
	} else {
		printf("error: expected name or (dcl)\n");
	}
	
	int type;
	while ( (type = gettoken()) == PARENS || type == BRACKETS
			|| type == '(')
		//如果函数声明中包含有非空白字符（即参数类型声明）
		if (type == '(') {
			strcat(out, " function (");
			while ((type = gettoken()) == NAME || type == ','
					|| type == '*') {
				strcat(out, " ");
				strcat(out, token);
			}
			strcat(out, ") returning");
		} else if (type == PARENS)
			strcat(out, " function returning");
		else {
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}
	//printf("type=%c\n", type);
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
		while ((c = getch()) == ' ' || c == '\t')
			;
		if (c == ')') {
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

#define BUFFSIZE 100
char buff[BUFFSIZE];
int bp = 0;

int getch(void)
{
	return (bp > 0) ? buff[--bp] : getchar();
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

