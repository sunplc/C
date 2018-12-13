#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORD_LEN 100

struct bin_tree {
	char *word;
	int times;
	struct bin_tree *left;
	struct bin_tree *right;
};

struct word_list {
	char *word;
	int times;
	struct word_list *next;
};

//从输入中获取一个单词(仅限字母数字或下划线组成)
int getword(char *word, int maxwordlen)
{
	int c, n = 0;
	while (isspace(c = getchar()))
		;
	if (isalnum(c) || c == '_') {
		*(word++) = c;
		++n;
		while (n <= maxwordlen && (isalnum(c = getchar()) || c == '_')) {
			*(word++) = c;
			++n;
		}
	}
	*word = '\0';
	return c;
}

struct bin_tree *tree_alloc(void)
{
	return (struct bin_tree *)malloc(sizeof(struct bin_tree));
}

char *Strdup(char *s)
{
	char *p;
	p = (char *)malloc(strlen(s) + 1);
	if (p != NULL)
		strcpy(p, s);
	return p;
}

struct bin_tree *addtree(struct bin_tree *p, char *w)
{
	int cond;
	if (p == NULL) {
		p = tree_alloc();
		p->word = Strdup(w);
		p->times = 1;
		p->left = p->right = NULL;
	} else if ( (cond = strcmp(w, p->word)) == 0) {
		p->times++;
	} else if (cond < 0) {
		p->left = addtree(p->left, w);
	} else {
		p->right = addtree(p->right, w);
	}
	return p;
}

struct word_list *list_alloc(void)
{
	return (struct word_list *)malloc(sizeof(struct word_list));
}

struct word_list *add_list(struct word_list *l, char *w, int times)
{
	if (l == NULL) {
		struct word_list *p = list_alloc();
		p->word = w;
		p->times = times;
		p->next = NULL;
		return p;
	} else {
		l->next = add_list(l->next, w, times);
		return l;
	}
}

struct word_list *tree_copy(struct bin_tree *p, struct word_list *l)
{
	if (p != NULL) {
		l = tree_copy(p->left, l);
		l = add_list(l, p->word, p->times);
		l = tree_copy(p->right, l);
	}
	return l;
}

void sort_list(struct word_list *l)
{
	int t;
	char *s;
	if (l != NULL && l->next != NULL) {
		if (l->times < l->next->times) {
			t = l->times;
			l->times = l->next->times;
			l->next->times = t;
			s = l->word;
			l->word = l->next->word;
			l->next->word = s;
		}
		sort_list(l->next);
	}
}

void sort_list_a(struct word_list *l, int len)
{
	if (l != NULL) {
		sort_list(l);
		if (--len > 0)
			sort_list_a(l, len);
	}
}

void list_print(struct word_list *p)
{
	if (p != NULL) {
		//单词过多，只打印出现次数大于一次的
		if (p->times > 2)
			printf("%4d %s\n", p->times, p->word);
		list_print(p->next);
	}
}

int get_list_len(struct word_list *l)
{
	if (l != NULL) {
		if (l->next != NULL) {
			return 1 + get_list_len(l->next);
		} else {
			return 1;
		}
	}
	return 0;
}

//按序打印树p
void treeprint(struct bin_tree *p)
{
	if (p != NULL) {
		treeprint(p->left);
		printf("%4d %s\n", p->times, p->word);
		treeprint(p->right);
	}
}

int main()
{
	struct bin_tree *root = NULL;
	struct word_list *list = NULL;
	char word[MAX_WORD_LEN];

	while (getword(word, MAX_WORD_LEN) != EOF) {
		if (isalnum(word[0]) || word[0] == '_')
			root = addtree(root, word);
	}
	list = tree_copy(root, list);
	int len = get_list_len(list);
	printf("list length = %d\n", len);
	sort_list_a(list, len);
	list_print(list);

	putchar('\n');
	//treeprint(root);

	return 0;
}

