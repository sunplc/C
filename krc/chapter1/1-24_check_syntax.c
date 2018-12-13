#include <stdio.h>

#define MAX_NEST 100	//括号和引号的最大嵌套层数
#define OUT 0			//当前字符不在注释中或字符串常量中
#define INLINE_IN 1		//当前字符在单行注释中
#define BLOCK_IN 2		//当前字符在块注释中
#define QUOTE_IN 3		//当前字符在字符串常量中

//练习 1-24. 编写一个程序，其用于检查 C程序的基本语法错误，
//例如不配对的圆括号、方括号和花括号。别忘了对单引号、双引号、转义序列以及注释的处理。
//（如果读者想把它写成完全通用的程序，难度会比较大。 ）
// 测试文本 syntax.txt

/* 规则：
 * 1.括号有三种，圆括号、方括号和花括号，括号必须是一对一对的配对的，
 * 一对括号内可以包含一对完整的括号，即括号嵌套；但是每对不同的括号之间不能交叉。
 * 2.单引号和双引号也需要配对，不同的引号也不能交叉。
 * 3.注释和字符串常量中的括号和引号忽略，不计入配对。
 */

int main(void)
{
	// c是当前字符，prevc是上一个字符，state代表当前是否在注释中，
	// quote_state表示当前是否在双引号中
	int prevc = 0, c, state = OUT, quote_state = OUT;

	//将数组s和变量index作为栈来使用，如果字符c是配对字符的开始符就将c入栈
	//如果字符c是配对字符的结束符时就出栈
	//error变量表示出错的次数
	int s[MAX_NEST], index  = 0, error = 0;

	while ((c = getchar()) != EOF) {
		// 不在注释中，才会检查是否匹配
		if (state == OUT) {
			// 不在双引号中(不是字符串常量)，才检查是否匹配
			if (quote_state == OUT) {
				if (c == '(' || c == '[' || c == '{') {
					s[index++] = c;
				} else if (c == ')') {
					//如果位于栈顶的字符和当前需要匹配的字符是一对
					if (s[index - 1] == '(')
						--index;
					else
						++error;
				} else if (c == ']') {
					if (s[index - 1] == '[')
						--index;
					else
						++error;
				} else if (c == '}') {
					if (s[index - 1] == '{')
						--index;
					else
						++error;
				}
			}

			// 当前字符是单引号，并且上一个字符不是反斜线，并且不是在双引号中
			if (c == '\'' && prevc != '\\' && quote_state == OUT) {
				if (s[index - 1] == '\'')
					--index;
				else
					s[index++] = c;
			} else if (c == '\"' && prevc != '\\') {
				if (s[index - 1] == '\"') {
					--index;
					if (quote_state == QUOTE_IN)
						quote_state = OUT;
				} else {
					s[index++] = c;
					quote_state = QUOTE_IN;
				}
			}
		}

		//单行注释开始
		if (prevc == '/' && c == '/') {
			if (state == OUT)
				state = INLINE_IN;
		}
		//块注释开始
		if (prevc == '/' && c == '*') {
			if (state == OUT)
				state = BLOCK_IN;
		}
		//单行注释结束
		if (c == '\n') {
			if (state == INLINE_IN)
				state = OUT;
		}
		//块注释结束
		if (prevc == '*' && c == '/') {
			if (state == BLOCK_IN)
				state = OUT;
		}

		prevc = c;
	}

	if (index > 0)
		error += index;

	if (error) {
		printf("有%d个语法错误!\n", error);
	} else {
		printf("没有语法错误!\n");
	}

	return 0;
}

