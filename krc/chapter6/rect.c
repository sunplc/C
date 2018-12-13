#include <stdio.h>

int main()
{
	// 1 可以用一个成员常值列表初始化结构；
	// 2 一个自动结构变量也可以通过赋值进行初始化
	struct point {
		int x;
		int y; 
	};
	struct point pt;
	//struct point pt = {4, 3}; //error
	pt.x = 4;
	pt.y = 3;

	printf("%d %d\n", pt.x, pt.y);
	double dist, sqrt(double);
	dist = sqrt((double)pt.x * pt.x + (double)pt.y * pt.y);
	printf("dist=%f\n", dist);

	struct rect {
		struct point pt1;
		struct point pt2;
	};

	struct rect screen;
	//screen = {{4,3},{15,18}};	//error
	
	screen.pt1.x = 4;
	screen.pt1.y = 3;
	screen.pt2.x = 15;
	screen.pt2.y = 18;
	
	//screen.pt1 = {4,3};	//error
	//screen.pt2 = {15,18}; //error
	
	//struct rect screen = { //correct
	//	{ 4,3 },
	//	{ 15,18 }
	//};

	dist = sqrt((double)(screen.pt1.x - screen.pt2.x) * (screen.pt1.x - screen.pt2.x) 
			+ (double)(screen.pt1.y - screen.pt2.y) * (screen.pt1.y - screen.pt2.y));
	printf("dist=%f\n", dist);
	return 0;
}

