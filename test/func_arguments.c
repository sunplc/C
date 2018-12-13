#include <stdio.h>

void func(){
//void func(void){
	puts("do nothing");
}

// 函数定义时,
// 参数列表为空,表示可以接受零个或多个参数;
// 参数列表为void,表示函数无参数,不能传递参数.
int main(void)
{
	//func();
	func(9, 2, 3, 4, 5);
	return 0;
}

