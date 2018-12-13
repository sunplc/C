#include <stdio.h>
#include <ctype.h>	// isdigit(), isalnum(), isblank()
#include <math.h>	// M_E, pow();
#include <string.h>	// strcmp()

#define MAXLINE 1000		//最大行宽
int Getline(char s[], int lim);	//获取一行输入

double atof_pro(char s[]);	//字符串转浮点数
void push(double f);		//将操作数压入栈顶
double pop(void);			//从栈顶弹出一个操作数
int getop(char s[]);		//获取下一个操作数或操作符

void print_top(void);		//打印栈顶元素
void exchange_top(void);	//交换栈顶元素的两个元素
double copy_top(void);		//复制栈顶元素
void clear(void);			//清空栈

#define MAXOP 100	//操作数或运算符的最大长度
#define NUMBER '0'	//标示找到一个数

char line[MAXLINE] = "";
int linep = 0;

int main(void)
{
	int type;
	double op2;
	char s[MAXOP];
	double x; //增加变量处理
	Getline(line, MAXLINE);

	while (linep != -1 && (type = getop(s)) != EOF)  {
		//printf("s = %s\n", s);
	 	//printf("type = %c\n", type);
		//printf("linep = %d\n", linep);
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
			break;
		case 'e':
			push(exp(pop()));
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

int getop(char *s)
{
	int i = 0, c, tmp;
	// 忽略空白字符
	tmp = line[linep];
	while ( isblank(*s = c = line[linep++]) ) {
		;
	}
	*(++s) = '\0';
	if (isdigit(c) || c == '-' || c == '.') {
		while (linep < MAXLINE && isdigit(*s++ = c = line[linep++]))
			;
		if (c == '.')
			while (linep < MAXLINE && isdigit(*(++s) = c = line[linep++]) )
				;
		--linep;		//读取位置回退一个字符，因为上面多读取了一个
		*s = '\0';	//增加字符串结束符

		//如果操作符只是一个减号
		if (tmp == '-' && i == 1) {
			return '-';
		} else {
			printf(">>>%s\n", s);
			return NUMBER;
		}
	} else {
		tmp = c;
		if (tmp == '\n') {
			linep = -1;
			return tmp;
		}
		while (linep < MAXLINE && isalnum(*(++s) = c = line[linep++]) )
			;
		*s = '\0';
		--linep;

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

/* getline：取一行放到 s 中，并返回该行的长度 */ 
int Getline(char s[], int lim)
{
	int c, i;
	i = 0;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n') {
		s[i++] = c;
	}
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
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

