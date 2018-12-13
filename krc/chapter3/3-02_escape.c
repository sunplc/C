#include <stdio.h>

#define MAX_LEN 1000

void escape(char s[], char t[])
{
	int i, j;
	for (i = 0, j = 0; j < MAX_LEN; ++i, ++j) {
		switch (t[i]) {
        case '\n':
            s[j] = '\\';
            s[++j] = 'n';
            break;
        case '\t':
            s[j] = '\\';
            s[++j] = 't';
            break;
        default:
            s[j] = t[i];
            break;
		}
	}
}

void unescape(char *s, char *t)
{
	int i = 0, j = 0;
	while (t[i] != '\0') {
		if (t[i] == '\\' && t[i+1] != '\0') {
			switch (t[++i]) {
            case 'n':
                s[j] = '\n';
                break;
            case 't':
                s[j] = '\t';
                break;
            default:
                s[j++] = '\\';
                s[j] = t[i];
                break;
			}
		} else {
			s[j] = t[i];
		}
		++i;
		++j;
	}
	// 别忘了结束符
	s[j] = t[i];
}

// 练习 3-2. 编写一个函数 escape(s,t)，其将字符串 t 复制到字符串 s 中，并在复制过程中
// 将换行符和制表符之类的字符转换为可见的转义字符序列，如 \n 与 \t。请使用一个
// switch 语句。再编写一个反向转换函数，其将转义字符序列转换为实际的字符。
int main()
{
	putchar('\a'); //输出字符\a会响铃
	
	char t2[] = "aa		bb";
	char s2[MAX_LEN];
	escape(s2, t2);
	
	printf("%s\n----------------------------\n", s2);
	
	char t[] = "aa\\waaaaaa\\rsd\\nsd\tf\\";
	char s[MAX_LEN];
	unescape(s, t);
	
	printf("%s\n", s);
	return 0;
}

