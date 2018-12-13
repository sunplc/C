/*
 * 实现简化版本的scanf函数
 */

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLEN 100

void minscanf(char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);

	int c;
	char *content = (char *) malloc(MAXLEN + 1);

	int *pi;
	float *pf;
	char *p = fmt, *temp;
	while ((c = getchar()) != EOF) {

		while (isspace(c))
			c = getchar();

		while (isspace(*p))
			++p;

		if (c != *p) {

			if (*p != '%')
				break;
			else
				++p;

			switch (*p++) {
				case 'd':
					temp = content;
					while (isdigit(c)) {
						*temp++ = c;
						c = getchar();
					}
					*temp = '\0';
					//printf("content=%s\n", content);
					pi = va_arg(ap, int *);
					*pi = atoi(content);
					break;
				case 'f':
					temp = content;
					while (isdigit(c) || c == '.') {
						*temp++ = c;
						c = getchar();
					}
					*temp = '\0';
					//printf("content2=%s\n", content);
					pf = va_arg(ap, float *);
					*pf = atof(content);
					break;
				case 's':
					temp = content;
					while (c != EOF && c != '\n') {
						*temp++ = c;
						c = getchar();
					}
					*temp = '\0';
					temp = va_arg(ap, char *);
					//printf("content = %s\n", content);
					strcpy(temp, content);
					break;
				default:
					putchar(*p);
					break;
			}
		}
		if (*p == EOF || *p == 0)
			break;
	}

	va_end(ap);
}

int main(int argc, char *argv[])
{
	printf("please input:\n");

	int d = 0;
	minscanf("%d", &d);
	printf("d = %d\n", d);

	float f;
	minscanf("%f", &f);
	printf("f = %f\n", f);

	char s[30];
	minscanf("%s", s);
	printf("s = %s\n", s);

	minscanf("%d %f %s", &d, &f, s);

	printf("d = %d\n", d);
	printf("f = %f\n", f);
	printf("s = %s\n", s);
	return 0;
}

