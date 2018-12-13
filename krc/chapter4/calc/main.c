#include <stdio.h>
#include <math.h>	// M_E, pow();
#include <ctype.h>	// isspace();
#include "calc.h"

#define MAXOP 100	//操作数或运算符的最大长度

int main(void)
{
	printf("请输入逆波兰表达式：\n");
	int type;
	double op2;
	char s[MAXOP];
	double x; //增加变量处理

	while ( (type = getop(s)) != -1) {
		//printf("s = %s MARK\n", s);
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
			double op3 = pop();
			printf("%g %g\n", op2, op3);
			push(op3 - op2);
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
			printf("请输入逆波兰表达式：\n");
			break;
		case -1:
			printf("EOF\n");
			break;
		default:
			printf("error: 未知命令 %s\n", s);
			break;
		}
	}
	return 0;
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

