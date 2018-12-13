#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h> // malloc

#include "getword_with_lineno.h"

#define MAX_WORD_LEN 100

struct linelist {
	int lineno;
	struct linelist *next;
};

struct wordlist {
	char *word;
	struct wordlist *left;
	struct wordlist *right;
	struct linelist *lp;
};

struct wordlist *addlist(struct wordlist *p, char *w, int lineno);
struct linelist *addlinelist(struct linelist *p, int lineno);
struct wordlist *lalloc(void);
struct linelist *llalloc(void);
char *Strdup(char *s);
void treeprint(struct wordlist *p);
void linelist_print(struct linelist *p);

// 练习 6-3.
// 编写一个交叉引用程序，打印一个文档中所有单词的列表，
// 并打印每个单词出现的行的行数列表。
// 去掉如“the”、“and”等干扰性单词
//
// 使用word.txt作为标准输入
int main()
{
	char word[MAX_WORD_LEN];
	int lineno = 0;
	struct wordlist *root = NULL;

	while (getword(word, MAX_WORD_LEN, &lineno) != EOF) {
		//printf("mark %d\n", lineno);
		if (isalpha(word[0]) || word[0] == '_') {
			root = addlist(root, word, lineno);
		}
	}
	treeprint(root);
	return 0;
}

struct wordlist *addlist(struct wordlist *p, char *w, int lineno)
{
	int cond;
	if (p == NULL) {
		p = lalloc();
		p->word = Strdup(w);
		p->left = p->right = NULL;
		p->lp = NULL;
		p->lp = addlinelist(p->lp, lineno);
	} else if ((cond = strcmp(w, p->word)) == 0) {
		p->lp = addlinelist(p->lp, lineno);
	} else if (cond < 0)
		p->left = addlist(p->left, w, lineno);
	else
		p->right = addlist(p->right, w, lineno);
	return p;
}

struct linelist *addlinelist(struct linelist *p, int lineno)
{
	if (p == NULL) {
		p = llalloc();
		p->lineno = lineno;
		p->next = NULL;
	} else if (lineno < p->lineno) {
		struct linelist *p_temp = llalloc();
		p_temp->lineno = lineno;
		p_temp->next = p->next;
		p->next = p_temp;
		//printf("%d %d\n", p->lineno, p_temp->lineno);

		int temp;
		temp = p->lineno;
		p->lineno = p_temp->lineno;
		p_temp->lineno = temp;
		//printf("%d %d\n", p->lineno, p_temp->lineno);
	} else if (lineno > p->lineno) {
		p->next = addlinelist(p->next, lineno);
	}
	return p;
}

struct wordlist *lalloc(void)
{
	return (struct wordlist *)malloc(sizeof(struct wordlist));
}

//为一个链表分配内存
struct linelist *llalloc(void)
{
	return (struct linelist *)malloc(sizeof(struct linelist));
}

//新创建一个字符串，复制字符串s到其中并返回其地址
char *Strdup(char *s)
{
	char *p;
	p = (char *)malloc(strlen(s) + 1);
	if (p != NULL)
		strcpy(p, s);
	return p;
}

void treeprint(struct wordlist *p)
{
	if (p != NULL) {
		treeprint(p->left);
		if (strcmp(p->word, "the") != 0
			&& strcmp(p->word, "and") != 0) {
			printf("%s\n", p->word);
			linelist_print(p->lp);
		}
		treeprint(p->right);
	}
}

void linelist_print(struct linelist *p)
{
	if (p != NULL) {
		printf("\tline: %d\n", p->lineno);
		linelist_print(p->next);
	}
}

