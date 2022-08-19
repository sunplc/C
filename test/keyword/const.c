/*
 * 被 const 关键字修饰的变量，是“只读变量”，无法在后续程序中修改其对应或指针指向的值。
 * const 修饰的变量，不具备“常量表达式”的属性，无法用来表示定长数组的长度等操作。
 * 常量表达式本身会在程序编译时被求值，而只读变量的值只能够在程序实际运行时才被得知。
 *
 * const cx = 3;
 * int arr[cx] = {1,2,3};
 *
 * 以上代码会报错
 *
 */
#include <stdio.h>

int main(void)
{
	int i1 = 1, i2 = 2, i3 = 3, i4 = 4, i5 = 5;

	// const 向右结合，修饰它右边最近的变量名或指针符*。
	// 如果const右边最近的是变量名，表示a（即变量）是只读；如果const右边最近的是指针，表示*（即指针）是只读。
	// const int 和 int const 效果一样。
	// const int *p中const靠近*所以修饰*，int * const p中const靠近p所以修饰p;
	
	const int i = -99;
	//++i; // wrong read-only variable
	int const j = 99; //和上一句效果相同
	//++j; // wrong read-only variable

	// "const int *a" equals "int const *a", The value of the address which 'a' pointed is read-only.
	const int *a = &i1;
	++a;		// correct, increment pointer a's pointed address with four bytes
	//++(*a);	// read-only wrong, can not change the value of the address that pointer 'a' pointed
	++i1;		// Correct

	int const *b = &i2; //和上一句效果相同
	++b;		// correct
	//++(*b);	// wrong read-only

	int * const c = &i3;
	//++c;		// wrong read-only
	++(*c);		// correct

	int const * const d = &i4;
	//++(c);	// wrong read-only 
	//++(*c);	// wrong read-only

	const int const *e = &i5; //有一个const是多余的
	++(e);		// correct
	//++(*e);	// wrong read-only

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
