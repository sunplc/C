#include <stdio.h>
#include <ctype.h>

#define MAX_LEN 1000

void expand(char *s1, char *s2)
{
	char start = 0, end = 0;
	int pstart = -1, pend = -1;

	int i;
	for (i = 1; s1[i+1] != '\0'; ++i) {
		if (s1[i] == '-') {
			if (isdigit(s1[i-1]) && isdigit(s1[i+1]) && s1[i-1] < s1[i+1]) {
				if (start == 0) {
					start = s1[i-1];
					end = s1[i+1];
					pstart = i-1;
					pend = i+1;
				} else {
					if (pend == i-1 && isdigit(s1[i+1]) && end < s1[i+1]) {
						end = s1[i+1];
						pend = i+1;
					}
				}
			}
			if (isalpha(s1[i-1]) && isalpha(s1[i+1]) && s1[i-1] < s1[i+1]) {
				if (start == 0) {
					start = s1[i-1];
					end = s1[i+1];
					pstart = i-1;
					pend = i+1;
				} else {
					if (pend == i-1 && isalpha(s1[i+1]) && end < s1[i+1]) {
						end = s1[i+1];
						pend = i+1;
					}
				}
			}
		}
	}
	//printf("start = %c, end = %c\n", start, end);
	
	pstart = pend = -1;
	char start2 = 0, end2 = 0;
	for (i = 1; s2[i+1] != '\0'; ++i) {
		if (s2[i] == '-') {
			if (s2[i-1] == start && isdigit(s2[i-1]) && isdigit(s2[i+1]) && s2[i-1] < s2[i+1]) {
				if (pstart == -1) {
					start2 = s2[i-1];
					end2 = s2[i+1];
					pstart = i-1;
					pend = i+1;
				} else {
					if (pend == i-1 && isdigit(s2[i+1]) && end2 < s2[i+1]) {
						end2 = s2[i+1];
						pend = i+1;
					}
				}
			}
			if (isalpha(s2[i-1]) && isalpha(s2[i+1]) && s2[i-1] < s2[i+1]) {
				if (pstart == -1) {
					start2 = s2[i-1];
					end2 = s2[i+1];
					pstart = i-1;
					pend = i+1;
				} else {
					if (pend == i-1 && isalpha(s2[i+1]) && end2 < s2[i+1]) {
						end2 = s2[i+1];
						pend = i+1;
					}
				}
			}
		}
	}
	//printf("start = %c, end = %c\n", start2, end2);

	if (start == start2 && end == end2) {
		char tmp[MAX_LEN];
		for (i = 0; s2[pend+i+1] != '\0'; ++i) {
			tmp[i] = s2[pend+i+1];
		}
		tmp[i] = s2[pend+i+1];

		for(i = 0; i < (end - start + 1); ++i) {
			s2[pstart+i] = start+i;
		}

		int new_end = pstart+i;
		for (i = 0; tmp[i] != '\0'; ++i) {
			s2[new_end+i] = tmp[i];
		}
		s2[new_end+i] = tmp[i];
	}
}

// 练习 3-3. 编写一个 expand(s1, s2)，它将字符串 s1 中类似 a-z 的速记符在 s2中扩展为
// 等价的完全列表 abc…xyz。函数支持大小写字符和数字，并可处理 a-b-c、a-z0-9
// 以及-a-z之类的用例。打头和结尾的 - 按普通字符处理。
int main()
{
	char s1[MAX_LEN] = "--a-n0-3-9-";
	char s2[MAX_LEN] = ">>a-n-666666-";
	expand(s1, s2);
	printf("s2 = %s\n", s2);
	return 0;
}

