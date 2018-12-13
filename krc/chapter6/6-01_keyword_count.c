#include <stdio.h>
#include <ctype.h>
#include <string.h>

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

int getword(char *, int);
int binsearch(char *, struct key *, int);

//计算c的关键字
int main(int argc, char *argv[])
{
	int n;
	char word[MAXWORD];

	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
			if ((n = binsearch(word, keytab, NKEYS)) >= 0)
				keytab[n].count++;

	for (n = 0; n < NKEYS; n++)
		if (keytab[n].count > 0)
			printf("%4d %s\n", keytab[n].count, keytab[n].word);
				
	return 0;
}

//从输入中获取一个单词(仅限字母组成)
int getword(char *word, int maxwordlen)
{
	int c, n = 0;
	while (isspace(c = getchar()))
		;
	if (isalpha(c)) {
		*(word++) = c;
		++n;
		while (n <= maxwordlen && isalpha(c = getchar())) {
			*(word++) = c;
			++n;
		}
	}
	*word = '\0';
	return c;
}

//在keytab中搜索word，搜索到则返回数组下标，否则返回-1
int binsearch(char *word, struct key *keytab, int len)
{
	//printf("word=%s %d\n", word, (int)strlen(word));
	int low = 0, mid, high = len - 1;
	char *keyword;
	int rs;

	while (low <= high) {
		mid = (low + high) / 2;
		//printf(">>> low %d %d %d\n", low,mid, high);
		keyword = keytab[mid].word;
		rs = strcmp(keyword, word);
		//printf("%s %s %d\n", keyword, word, rs);
		if (rs > 0) {
			high = mid - 1;
		} else if (rs < 0) {
			low = mid + 1;
		} else {
			return mid;
		}
	}
	return -1;
}

