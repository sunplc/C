#include <stdio.h>
#include <ctype.h>	// isdigit(), isalnum()
#include <math.h>	// M_E, pow();
#include <string.h>	// strcmp()

double atof_pro(char s[]);
void push(double f);
double pop(void);
int getop(char s[]);
int getch(void);
void ungetch(int c);		//将字符压回输入缓冲中
void ungets(char *s);		//将整个字符串压回输入缓冲中

void print_top(void);		//打印栈顶元素
void exchange_top(void);	//交换栈顶元素的两个元素
double copy_top(void);		//复制栈顶元素
void clear(void);			//清空栈

#define MAXOP 100	//操作数或运算符的最大长度
#define NUMBER '0'	//标示找到一个数

int main(void)
{
	int type;
	double op2;
	char s[MAXOP];
	double x; //增加变量处理
	//ungets("1 3 +");
	while ( (type = getop(s)) != EOF) {
		//printf("s = %s\n", s);
		switch (type) {
		case NUMBER:
			push(atof_pro(s));
			break;
		case '+':
			push(pop() + pop());
			break;
		case '*':
			push(pop() * pop());
			break;
		case '-':
			//print_top();
			//printf("top = %g\n", copy_top());
			//exchange_top();
			//clear();
			op2 = pop();
			push(pop() - op2);
			break;
		case '/':
			op2 = pop();
			if (op2 != 0.0)
				push(pop() / op2);
			else
				printf("error: 除零溢出\n");
			break;
		case '%':
			op2 = pop();
			if (op2 != 0.0)
				push( ((int)pop()) % ((int)op2));
			else
				printf("error: 取模时除零溢出\n");
			break;
		case 's':
			push(sin(pop()));
			//print_top();
			break;
		case 'e':
			push(exp(pop()));
			print_top();
			break;
		case 'p':
			op2 = pop();
			push(pow(pop(), op2));
			break;
		case 'x':		// x表示变量x
			printf("x = %g\n", x);
			break;
		case '\n':
			x = pop();
			printf("Result: %.8g\n", x);
			break;
		default:
			printf("error: 未知命令 %s\n", s);
			break;
		}
	}
	return 0;
}

int getop(char s[])
{
	int i = 0, c, tmp;
	static int buf = EOF;
	//printf("MARK-%d\n", buf);
	if (buf != EOF && !isblank(buf)) {
		s[0] = c = buf;
	} else {
		// 忽略空白字符
		while (isblank(s[0] = c = getchar())) {
			;
		}
	}
	buf = EOF;
	s[1] = '\0';
	if (isdigit(c) || c == '-' || c == '.') {
		while (isdigit(s[++i] = c = getchar()))
			;
		if (c == '.')
			while (isdigit(s[++i] = c = getchar()))
				;
		s[i] = '\0';
		buf = c;
		return NUMBER;
	} else {
		tmp = c;
		if (tmp == '\n')
			return tmp;

		while (isalnum(s[++i] = c = getchar()))
			;
		s[i] = '\0';
		buf = c;

		if (strcmp(s, "sin") == 0) 
		{
			return 's';
		} 
		else if (strcmp(s, "exp") == 0)
		{
			return 'e';
		}
		else if (strcmp(s, "pow") == 0)
		{
			return 'p';
		}
		else if (strcmp(s, "x") == 0)
		{
			return 'x';
		}
		else 
		{
			return tmp;//这不是数字
		}
	}
}

//可以处理科学记数法的“字符串转浮点数”函数
double atof_pro(char s[])
{
	double val, power;
	int i, sign;
	for (i = 0; isspace(s[i]); ++i) //略过空白符
		;
	sign = s[i] == '-' ? -1 : 1;
	if (s[i] == '+' || s[i] == '-') //略过正负号
		i++;
	for (val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');
	if (s[i] == '.') //略过小数点
		i++;
	for (power = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0');
		power *= 10.0;
	}
	// 统计e的指数
	int power_e = 0, sign_e = 1;
	if (s[i] == 'e' || s[i] == 'E') {
		i++;
		sign_e = s[i] == '-' ? -1 : 1;
		if (s[i] == '+' || s[i] == '-')
			i++;
		for ( ; isdigit(s[i]); i++) {
			power_e = power_e * 10 + (s[i] - '0');
		}
		power_e *= sign_e;
	}
	return sign * val / power * pow(M_E, power_e);
}

#define MAXVAL 100	//栈stack的最大深度

double stack[MAXVAL]; //栈stack
int sp = 0; //栈stack的下一个空闲位置

void push(double f)
{
	if (sp < MAXVAL)
		stack[sp++] = f;
	else
		printf("error: 栈满，不能将%g压栈\n", f);
}

double pop(void)
{
	if (sp > 0) {
		return stack[--sp];
	} else {
		printf("error: 栈空\n");
		return 0.0;
	}
}

//打印栈顶元素
void print_top(void)
{
	if (sp > 0) {
		printf("stack top: %g\n", stack[sp - 1]);
	} else {
		printf("stack is empty!\n");
	}
}

//复制栈顶元素
double copy_top(void)
{
	if (sp > 0) {
		return stack[sp - 1];
	} else {
		return 0.0;
	}
}

//交换栈顶的两个元素
void exchange_top(void)
{
	if (sp > 1) {
		double tmp = stack[0];
		stack[0] = stack[1];
		stack[1] = tmp;
	}
}

//清空栈
void clear(void)
{
	sp = 0;
}

#define BUFSIZE 100
char buf[BUFSIZE];	//供ungetch函数使用的缓冲区
int bufp = 0;		//buf中的下一个空闲位置

int getch(void)
{
	if (bufp > 0) {
		return buf[--bufp];
	} else {
		int c = getchar();
		if (c == EOF) {
			return -1;
		} else {
			return c;
		}
	}
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if (c == EOF)
		return ;
	if (bufp >= BUFSIZE) {
		printf("ungetch: 压回字符过多\n");
	} else {
		buf[bufp++] = c;
	}
}

void ungets(char *s)
{
	int i, len;
	len = strlen(s);
	if (len > 0)
		ungetch('\n');
	for (i = len - 1; i >= 0; --i) {
		ungetch(s[i]);
	}
}

