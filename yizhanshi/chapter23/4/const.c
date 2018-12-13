// Vim: Better, Stronger, Faster
#include <stdio.h>

int main(void)
{
	int i1 = 1, i2 = 2, i3 = 3, i4 = 4, i5 = 5;

	
	// const 向右结合，修饰它右边最近的变量或指针。
	// const在*号前，表示int（即指向的地址的值）是只读；const在*后表示指针（即指针）是只读。
	// const int 和 int const 一样。const int *p中const修饰int，int * const p中const靠近p所以修饰p;

	// "const int *a" equals "int const *a", The value of the address which 'a' pointed is read-only.
	const int *a = &i1;
	++a;		// correct, increment pointer a's pointed address with four bytes
	//++(*a);	// read-only wrong, can not change the value of the address that pointer 'a' pointed
	++i1;		// Correct

	int const *b = &i2;
	++b;		// correct
	//++(*b);	// read-only wrong

	int * const c = &i3;
	//++c;		// read-only wrong
	++(*c);		// correct

	int const * const d = &i4;
	//++(c);	// read-only wrong
	//++(*c);	// read-only wrong

	const int const *e = &i5;
	++(e);		// correct
	//++(*e);		// read-only wrong

	printf("\n*********************\n");
	printf("%p\n", a);
	printf("%p\n", b);
	printf("%p\n", c);
	printf("%p\n", d);
	printf("%p\n", e);
	printf("\n*********************\n");
	printf("%d\n", *a);
	printf("%d\n", *b);
	printf("%d\n", *c);
	printf("%d\n", *d);
	printf("%d\n", *e);
	return 0;
}
