#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

struct nlist {			//表项
	struct nlist *next;	//链表中的后续项
	char *name;			//所定义的名字
	char *defn;			//替换文本
};

#define HASHSIZE 101

static struct nlist *hashtab[HASHSIZE];

// hash: 形成字符串s的hash值
unsigned hash(char *s)
{
	unsigned hashval;

	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % HASHSIZE;
}

// lookup: 在hashtab中查找s
struct nlist *lookup(char *s)
{
	struct nlist *np;
	for (np = hashtab[hash(s)]; np != NULL; np = np->next)
		if (strcmp(s, np->name) == 0)
			return np;	//找到
	return NULL;		//未找到
}

// install: 将 (name, defn) 放到hashtab中
struct nlist *install(char *name, char *defn)
{
	struct nlist *np;
	unsigned hashval;

	if ((np = lookup(name)) == NULL) {	//如果未找到
		np = (struct nlist *)malloc(sizeof(*np));
		if (np == NULL || (np->name = strdup(name)) == NULL)
			return NULL;
		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	} else {	//已经有了
		free((void *)np->defn);	//将原有的 defn 释放
	}

	if ((np->defn = strdup(defn)) == NULL)
		return NULL;
	return np;
}

// 练习 6-5. 编写一个 undef 函数，
// 它从 lookup 与 install 维护的表中删除某个名字及定义。
void undef(char *name, char *defn)
{
	struct nlist *np, *prev;
	for (prev = np = hashtab[hash(name)]; np != NULL; prev = np, np = np->next)
		if (strcmp(name, np->name) == 0)
			break;
	if (np != NULL) {
		if (strcmp(defn, np->defn) == 0) {
			unsigned hashval = hash(name);
			if (prev == hashtab[hashval])
				hashtab[hashval] = np->next;
			else
				prev->next = np->next;
			free((void *)np);
			//free((void *)&np);
		}
	}
}

void print_hashtab(struct nlist* hashtab[], int size)
{
	int i;
	struct nlist *np;
	for (i = 0; i < size; i++) {
		if (hashtab[i] != NULL) {
			for (np = hashtab[i]; np != NULL; np = np->next)
				printf("hashtab[%3d]: %s => %s\n", i, np->name, np->defn);
		} else {
			//printf("hashtab[%d]: NULL\n", i);
		}
	}
	
}

#define BUFFSIZE 200
char buff[BUFFSIZE];
int bp = 0;

int getch(void)
{
	if (bp > 0)
		return buff[--bp];
	else
		return getchar();
}

void ungetch(int c)
{
	if (bp < BUFFSIZE)
		buff[bp++] = c;
	else {
		printf("Error: buff overflowed!\n");
		exit(1);
	}
}

int getword(char *word, int max_word_len)
{
	int c, i = 0;
	// 忽略空格符和制表符
	//while (isblank(c = getch()))
		//;
	c = getch();

	*word++ = c;
	++i;
	if (!(isalnum(c) || c == '_')) {
		*word = '\0';
		return c;
	}

	// 获取单词
	while (i < max_word_len && (isalnum(c = getch()) || c == '_')) {
		*word++ = c;
		++i;
	}

	*word = '\0';
	ungetch(c);
	return c;
}

#define MAX_WORD_LEN 30	//最大单词长度
#define NOT_NL 0		//word不是一个换行符
#define IS_NL 1			//word是一个换行符
#define NOT_WHITESPACE 0		//word不是一个空格符
#define IS_WHITESPACE 1			//word是一个空格符


// 练习 6-6. 基于本节的函数，实现一个简单的（譬如没有参数）适用于 C 程序的
// #define 处理器版本。你可能还会发现 getch 和 ungetch 有帮助
int main()
{
	char word[MAX_WORD_LEN + 1],
		last_word[MAX_WORD_LEN + 1],
		name[MAX_WORD_LEN + 1],
		defn[MAX_WORD_LEN + 1];
	int c,
		flag = 0,
		is_nl = NOT_NL,
		last_is_nl = NOT_NL,
		last_output_is_whitespace = NOT_WHITESPACE;

	struct nlist *np;

	while ((c = getword(word, MAX_WORD_LEN)) != EOF) {

		if (isblank(word[0])) {
			if (last_output_is_whitespace == NOT_WHITESPACE) {
				putchar(' ');
				last_output_is_whitespace = IS_WHITESPACE;
			}
			continue;
		}

		// 当单词是#时
		if (flag == 0 && strcmp(word, "#") == 0) {
			++flag;
		// #号后面紧跟着的单词时define
		} else if (flag == 1 && strcmp(word, "define") == 0) {
			++flag;
		// 再然后的单词是define语句的name
		} else if (flag == 2 && (isalnum(word[0]) || word[0] == '_')) {
			++flag;
			if (strncpy(name, word, MAX_WORD_LEN + 1) == NULL)
				flag = 0;
		// 再然后的单词是define语句的defn
		} else if (flag == 3 && (isalnum(word[0]) || word[0] == '_')) {
			++flag;
			if (strncpy(defn, word, MAX_WORD_LEN + 1) == NULL)
				flag = 0;
		} else {
			if (flag == 1 && strcmp(last_word, "#") == 0)
				putchar('#');
			flag = 0;
		}

		strcpy(last_word, word);

		if (flag == 4) {
			install(name, defn);
		}

		if (flag == 0) {
			if (isalnum(word[0]) || word[0] == '_') {
				np = lookup(word);
				if (np != NULL) {
					printf("%s", np->defn);
				} else {
					printf("%s", word);
				}
				last_output_is_whitespace = NOT_WHITESPACE;
			} else {
				//判断当前单词是否是换行符
				if (strcmp(word, "\n") == 0)
					is_nl = IS_NL;
				else
					is_nl = NOT_NL;

				//忽略连续的多个换行符，只输出一个
				if ( !(is_nl == IS_NL && last_is_nl == IS_NL)) {

					printf("%s", word);

					if ( is_nl == IS_NL || strcmp(word, " ") == 0)
						last_output_is_whitespace = IS_WHITESPACE;
					else
						last_output_is_whitespace = NOT_WHITESPACE;
				}

				last_is_nl = is_nl;
			}
		}
	}

	//print_hashtab(hashtab, HASHSIZE);

	return 0;
}

