#include <stdio.h>

#include "somefile.h"

// 关键词 extern 
// extern意为“外部的”，与internal相对；
//
// 因为c语言不允许在函数中定义函数，所以函数之外的变量都是外部变量；
// 函数内声明的变量都是内部变量或称之为局部变量或自动变量，包括函数参数。
//
// 如果一个外部变量在定义之前就需要被使用，或者该外部变量定义在与使用它
// 的源文件不同的源文件中，那么可以使用关键词 extern声明该变量，以扩展其作用域。
//
// 个人备注：
// 当需要使用一个变量但是程序中还没有发现该变量的声明或定义，就可以使用
// extern关键词来将该变量声明为一个“外部”变量，
// 编译器就会在整个程序文件和所有被包含文件中寻找该变量的定义。
// 在c语言中函数的声明和定义是在所有文件中可见的，
// 所以只要被调用函数是在同一个文件或被包含文件中定义的，调用之前就不需要使用extern来声明


// extern声明可以在函数外，也可以在函数内
//extern int var;
//extern int xx;

int main(void)
{
	extern int var;
	extern int xx;
	printf("var = %d\n", var);
	printf("xx = %d\n", xx);
	nothing();
	return 0;
}

int xx = 1234;

