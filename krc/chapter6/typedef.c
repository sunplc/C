#include <stdio.h>
#include <stdlib.h>

typedef struct tnode *Treeptr;

typedef struct tnode { /* 树节点 */
	char *word; /* 指向单词的文本 */
	int count; /* 出现次数 */
	Treeptr left; /* 左孩子 */
	Treeptr right; /* 右孩子 */
} Treenode; 

Treeptr talloc(void)
{
	return (Treeptr) malloc(sizeof(Treenode));
}


int main()
{
	typedef int Length;
	Length len, maxlen;
	len = 0, maxlen = 100;
	printf("%d %d\n", len, maxlen);

	typedef char * String;
	String p, str, alloc(int);
	int strcmp(String, String);
	p = (String) malloc(100);
	str = (String) malloc(100);
	printf("%p %p %ld\n", p, str, str-p);


	return 0;
}

