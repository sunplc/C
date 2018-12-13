#include <stdio.h>

typedef struct {
	int number;
	char *msg;
} unit_t;

void func(const unit_t *p);

void func(const unit_t *p)
{
	printf("%s\n", p->msg);
}

void func2(const int a)
{
	printf("func2: a = %d\n", a);
}

int main(void)
{
	unit_t unit1 = {3, "hahaha!"};
	const unit_t *p = &unit1;
	func(p);
	int a  = 7;
	func2(a);
	return 0;
}

