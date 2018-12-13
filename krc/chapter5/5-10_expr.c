#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#define MAXOP 100
#define OPMAXLEN 100

double stack[MAXOP];
int sp = 0;

void push(double f)
{
	if (sp < MAXOP)
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

int getop(char s[], char op[])
{
	int i = 0, j = 0;
	// 忽略空白字符
	while (isspace(s[i]))
		++i;

	if (isdigit(s[i]) || s[i] == '-' || s[i] == '.') {
		//如果不是负号而是减号
		if (s[i] == '-' && !isdigit(s[i+1])) {
			op[j] = '-';
			op[j+1] = '\0';
			return 1;
		}
		while (isdigit(s[i])) {
			op[j++] = s[i];
			++i;
		}

		if (s[i] == '.') {
			++i;
			while (isdigit(s[i])) {
				op[j++] = s[i];
				++i;
			}
		}
		op[j] = '\0';
		return 0;
	} else {
		if (isalnum(s[i]) || s[i] == '+' || s[i] == '-' || s[i] == '*'
				|| s[i] == '/' || s[i] == '%') {
			op[j++] = s[i];
			while (isalnum(s[i])) {
				op[j++] = s[i];
				++i;
			}
			op[j] = '\0';
			return 1;
		} else {
			printf("mark %c\n", s[i]);
			op[j] = '\0';
			return -1;
		}
	}
}

int main(int argc, char *argv[])
{
	char op[OPMAXLEN];
	if (argc < 2) {
		printf("Too few arguments\n");
		return 1;
	} else {
		int i, rs;
		for (i = 1; i < argc; i++)  {
			rs = getop(argv[i], op);
			printf("%s op = %s, rs=%d\n", argv[i], op, rs);
			if (rs == 0) {
				push(atof_pro(op));
			} else if (rs == 1) {
				printf("strlen = %d\n", strlen(op));
			
				double op2 = 0.0;
				if (strcmp(op, "+") == 0) {
					push(pop() + pop());
				} else if (strcmp(op, "-") == 0) {
					op2 = pop();
					push(pop() - op2);
				} else if (strcmp(op, "/") == 0) {
					op2 = pop();
					push(pop() / op2);
				} else if (strcmp(op, "*") == 0) {
					push(pop() * pop());
				} else {
					printf("未定义运算符\n");
					return 1;
				}
			}
		}
		printf("Result: %g\n", pop());
	}
	return 0;
}
