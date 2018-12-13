#include <stdio.h>

union u_tag {
	int ival;
	float fval;
	char *sval;
};

#define NSYM 100

struct {
	char *name;
	int flags;
	int utype;
	union u_tag u;
	//union {
	//	int ival;
	//	float fval;
	//	char *sval;
	//} u;
} systab[NSYM];

int main()
{
	systab[0].u.ival = 7;
	printf("%d\n", systab[0].u.ival);

	systab[0].u.fval = 5.34;
	printf("%f\n", systab[0].u.fval);
	printf("%d\n", systab[0].u.ival);

	printf("%p\n", systab[0].u.sval);
	
	//联合只可以使用其第一个成员类型的值进行初始化
	union u_tag u = {6.3};
	printf("%d\n", u.ival);
	printf("%f\n", u.fval);
	return 0;
}

