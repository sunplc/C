#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "getword.h"

#define MAXWORD 100
#define DEFAULT_COMPARE_LEN 6

//节点包含一个字符串的单链表
struct linkedlist {
	char *word;
	struct linkedlist *next;
};

// “三叉树”，middle指针指向链表
struct tnode {
	char *word;
	struct tnode *left;
	struct linkedlist *middle;
	struct tnode *right;
};

struct tnode *addtree(struct tnode *p, char *w, int n);
void treeprint(struct tnode *);
struct tnode *talloc(void);
char *Strdup(char *);

struct linkedlist *addlinkedlist(struct linkedlist *p, char *w);
void linkedlistprint(struct linkedlist *p, char *middle_word);
struct linkedlist *llalloc(void);

//编写一个程序，它读取一个 C 程序并按字母序将变量名分组打印出来，
//前 6 个字符相同（而之后有所不同）的变量分为一组。
//不要计算字符串和注释内的单词。
//将 6改为一个参数，可以通过命令行进行设置
//
// 使用variable_name.txt作为标准输入
int main(int argc, char *argv[])
{
	//获取比较字符串的长度选项
	int n = 0;
	while (--argc > 0) {
		if (strncmp(*(++argv), "-n=", 3) == 0) {
			//printf("mark=%s,len=%d\n", (*argv+3), (int)sizeof(*argv+2));
			n = atoi(*argv+3);
		}
	}
	if (n == 0) {
		n = DEFAULT_COMPARE_LEN;
		printf("Use -n=x option to set compare length\n");
	}


	struct tnode *root;
	char word[MAXWORD];

	root = NULL;
	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]) || word[0] == '_')
			root = addtree(root, word, n);

	treeprint(root);
	return 0;
}

//添加一个三叉树节点
struct tnode *addtree(struct tnode *p, char *w, int n)
{
	int cond;
	if (p == NULL) {
		p = talloc();
		p->word = Strdup(w);
		p->left = p->right = NULL;
		p->middle = NULL;
	} else if ((cond = strncmp(w, p->word, n)) == 0) {
		if (strcmp(w, p->word) != 0)
			p->middle = addlinkedlist(p->middle, w);
	} else if (cond < 0)
		p->left = addtree(p->left, w, n);
	else
		p->right = addtree(p->right, w, n);
	return p;
}

//将一个字符串按字母序放入链表中的适当位置，如果已存在相同字符串则忽略
struct linkedlist *addlinkedlist(struct linkedlist *p, char *w)
{
	int cond;
	if (p == NULL) {
		p = llalloc();
		p->word = Strdup(w);
		p->next = NULL;
	} else if ( (cond = strcmp(w, p->word)) < 0) {
		struct linkedlist *p_temp = llalloc();
		p_temp->word = Strdup(w);
		p_temp->next = p->next;
		p->next = p_temp;
		//printf("%s %s\n", p->word, p_temp->word);

		//交换p的word和p_temp的word
		char *temp_pchar = p_temp->word;
		p_temp->word = p->word;
		p->word = temp_pchar;
		//printf("%s %s\n", p->word, p_temp->word);
	} else if ( cond > 0) {
		p->next = addlinkedlist(p->next, w);
	}
	return p;
}

//打印二叉树
void treeprint(struct tnode *p)
{
	if (p != NULL) {
		treeprint(p->left);
		if (p->middle != NULL) {
			linkedlistprint(p->middle, p->word);
		} else {
			printf("%s\n", p->word);
		}
		treeprint(p->right);
	}
}

//打印链表，链表中每个节点的字符串的前n个字符是相同的，并且是按照字母序排列的
void linkedlistprint(struct linkedlist *p, char *middle_word)
{
	//用空行和缩进将相同单词区分出来
	if (p != NULL) {
		if (middle_word != NULL) {
			putchar('\n');
			printf("\t%s\n", middle_word);
		}
		printf("\t%s\n", p->word);
		linkedlistprint(p->next, NULL);
		if (middle_word != NULL) {
			putchar('\n');
		}
	} else {
		if (middle_word != NULL)
			printf("%s\n", middle_word);
	}
}

//为一个二叉树分配内存
struct tnode *talloc(void)
{
	return (struct tnode *)malloc(sizeof(struct tnode));
}

//为一个链表分配内存
struct linkedlist *llalloc(void)
{
	return (struct linkedlist *)malloc(sizeof(struct linkedlist));
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

