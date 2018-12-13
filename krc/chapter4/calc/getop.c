#include <stdio.h>
#include <ctype.h>	// isdigit(), isalnum()
#include <string.h>	// strcmp()
#include "calc.h"

int getop(char s[])
{
	int i = 0, c, tmp;
	// 忽略空白字符
	while ((s[0] = c = getch()) == ' ' || c == '\t') {
		;
	}
	s[1] = '\0';
	if (isdigit(c) || c == '-' || c == '.') {
		while (isdigit(s[++i] = c = getch()))
			;
		if (c == '.')
			while (isdigit(s[++i] = c = getch()))
				;
		s[i] = '\0';
		ungetch(c);

		//如果操作符只是一个减号
		if (s[0] == '-' && i == 1) {
			return '-';
		} else {
			return NUMBER;
		}
	} else {
		tmp = c;
		if (tmp == '\n' || tmp == -1)
			return tmp;
		while (isalnum(s[++i] = c = getch()))
			;
		s[i] = '\0';
		ungetch(c);

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
