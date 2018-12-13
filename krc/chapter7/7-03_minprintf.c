#include <stdio.h>	//printf putchar
#include <stdarg.h>	//va_list va_start va_arg va_end
#include <ctype.h>	//isdigit
#include <string.h>	//strndup
#include <stdlib.h> //atoi

#include "itoa.h"

#define ALIGN_LEFT 1	//左对齐
#define ALIGN_RIGHT 0	//右对齐
#define MAXLEN 100

// 格式化字符串，限制整数部分和小数部分的长度，不足指定长度则用空格补齐
// str 待格式化的字符串
// is_negative 是否左对齐
// width 整数部分的最大长度, 小于等于0表示不限制长度
// precision 小数部分的最大长度，小于等于0表示不限制长度
char *str_format(char *str, int is_negative, int width, int precision)
{
	int int_len = 0, decimal_len = 0; //整数部分长度，小数部分长度
	char *tmp = str; //保存str的值

	//统计整数部分长度
	while (*str != '.' && *str) {
		if (width <= 0 || int_len < width)
			++int_len;
		++str;
	}
	
	//统计小数部分长度
	if (*str == '.') {
		++str;
		while (*str) {
			if (precision <= 0 || decimal_len < precision)
				++decimal_len;
			++str;
		}
	}

	//printf("--- %d %d --- %d %d ---\n", width, precision, int_len, decimal_len);
	str = tmp; //还原str到原来的值

	//分配一个确定长度的内存空间给字符串p
	int len = 0;
	if (width > 0)
		len += width;
	else
		len += int_len;

	if (precision > 0)
		len += precision;
	else
		len += decimal_len;

	char *p = (char *) malloc(len + 1 + 1); //len，加一个小数点，加一个字符串结束符
	tmp = p;

	//整数部分需要填充的空格长度
	int whitespace_len = (width > 0 && int_len > 0) ? (width - int_len) : 0;
	//小数部分需要填充的空格长度
	whitespace_len += (precision > 0 && decimal_len > 0) ? (precision - decimal_len) : 0;

	if (whitespace_len > 0 && is_negative == ALIGN_RIGHT) {
		while (whitespace_len-- > 0)
			*p++ = ' ';
	}

	//复制最大int_len长度的str的整数部分到p中
	while (*str != '.' && *str) {
		if (int_len-- > 0)
			*p++ = *str;
		++str;
	}

	//复制最大 decimal_len长度的str的小数部分到p中
	if (*str == '.') {
		*p++ = '.';
		++str;
		while (*str) {
			if (decimal_len-- > 0)
				*p++ = *str;
			++str;
		}
	}

	if (whitespace_len > 0 && is_negative == ALIGN_LEFT) {
		while (whitespace_len-- > 0)
			*p++ = ' ';
	}

	*p = '\0';
	return tmp; 
}

void minprintf(char *fmt, ...)
{
	va_list ap;	//依次指向每一个无名参数
	char *p, *sval;
	int ival;
	double dval;
	int is_negative = ALIGN_RIGHT, width, precision;	//是否左对齐，宽度，精度
	char *temp;

	va_start(ap, fmt);	//使ap指向第一个无名参数

	for (p = fmt; *p; p++) {
		width = precision = 0;
		if (*p != '%') {
			putchar(*p);
			continue;
		}

		//检查是否以负号开头，表示左对齐
		++p;
		if (*p == '-') {
			is_negative = ALIGN_LEFT;
			++p;
		}

		//获取宽度
		temp = p;
		while (isdigit(*p)) {
			++p;
		}
		if (p != temp)
			width = atoi(strndup(temp, p-temp+1));

		//获取精度
		if (*p == '.') {
			++p;
			temp = p;
			while (isdigit(*p)) {
				++p;
			}
			if (p != temp)
				precision = atoi(strndup(temp, p-temp+1));
		}
		//printf("is_negative:%d width:%d precision:%d\n", is_negative, width, precision);

		switch (*p) {
			case 'd':
				ival = va_arg(ap, int);	//获取下一个参数，并转换为int类型
				temp = itoa(ival);
				temp = str_format(temp, is_negative, width, precision);
				fputs(temp, stdout);

				break;
			case 'f':
				dval = va_arg(ap, double);	//获取下一个参数，并转换为double类型
				char *str = (char *) malloc(MAXLEN);
				snprintf(str, MAXLEN -1, "%f", dval);
				str = str_format(str, is_negative, width, precision);
				fputs(str, stdout);
				break;
			case 's':
				for (sval = va_arg(ap, char *); *sval; sval++)
					putchar(*sval);
				break;
			default:
				putchar(*p);
				break;
		}
	}

	va_end(ap);	//完成之后的清理工作
}

//简化版本的printf函数
int main()
{
	printf("str_format example: ---%s---\n", str_format("12345.12345", ALIGN_LEFT, 10, 2));

	minprintf("|%4.2d|\n", 123456);
	minprintf("|%6.4f|\n", 12345678.12345678);
	char *s = "hello";
	minprintf("|%s|\n", s);
	
	return 0;
}

