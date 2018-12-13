#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "getword.h"

#define MAXWORD 100

struct key {
	char *word;
	int count;
};

//c语言关键字
struct key keytab[] = {
	{"auto", 0},
	{"break", 0},
	{"case", 0},
	{"char", 0},
	{"const", 0},
	{"continue", 0},
	{"default", 0},
	{"do", 0},
	{"double", 0},
	{"else", 0},
	{"enum", 0},
	{"extern", 0},
	{"float", 0},
	{"for", 0},
	{"goto", 0},
	{"if", 0},
	{"int", 0},
	{"long", 0},
	{"register", 0},
	{"return", 0},
	{"short", 0},
	{"signed", 0},
	{"sizeof", 0},
	{"static", 0},
	{"struct", 0},
	{"switch", 0},
	{"typedef", 0},
	{"union", 0},
	{"unsigned", 0},
	{"void", 0},
	{"volatile", 0},
	{"while", 0}
};

#define NKEYS (sizeof(keytab) / sizeof(keytab[0]))

struct key *binsearch(char *, struct key *, int);

//计算c的关键字
int main(int argc, char *argv[])
{
	struct key *p;
	char word[MAXWORD];

	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
			if ((p = binsearch(word, keytab, NKEYS)) != NULL)
				p->count++;

	for (p = keytab; p < keytab + NKEYS; p++)
		if (p->count > 0)
			printf("%4d %s\n", p->count, p->word);
				
	return 0;
}

//折半查找
//在keytab中搜索word，搜索到则返回指针，否则返回NULL
struct key *binsearch(char *word, struct key *tab, int len)
{
	struct key *low, *mid, *high;
	low = &tab[0];
	high = &tab[len - 1];
	int rs;

	while (low <= high) {
		mid = low + (high - low) / 2;
		rs = strcmp(mid->word, word);
		if (rs > 0) {
			high = mid - 1;
		} else if (rs < 0) {
			low = mid + 1;
		} else {
			return mid;
		}
	}
	return NULL;
}

