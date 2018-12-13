#include <stdio.h>	// printf()
#include <ctype.h>	// isdigit() isspace()
#include <math.h>	// pow() , M_E 数学常数e 

#define MAXLINE 1000

// 练习 4-2. 对 atof 函数进行扩充，使之可以处理形如
//  123.45e-6
//  的科学计数法，即一个浮点数，其后可能紧跟 e 或 E 及一个（可能带正负号的）指数。
int main(void)
{
	double sum, atof(char []), atof_pro(char []);
	char line[MAXLINE];
	int Getline(char line[], int max);
	sum = 0;
	while (Getline(line, MAXLINE) > 0)
		printf("\t%g\n", sum += atof_pro(line));
	return 0;
}

double atof(char s[])
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
	return sign * val / power;
}

//可以处理科学记数法的 array to float
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

