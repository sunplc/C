#include <stdio.h>

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define XMAX 100

struct point {
	int x;
	int y;
};

struct rect {
	struct point pt1;
	struct point pt2;
};

/* makepoint：以 x 和 y 为坐标构造一个点 */
struct point makepoint(int x, int y)
{
	struct point p = {x, y};
	return p;
}

//结构参数像其他参数一样是按值传递的
struct point addpoint(struct point p1, struct point p2)
{
	p1.x += p2.x;
	p1.y += p2.y;
	return p1;
}

//判断一个点是否在一个矩形内
int ptinrect(struct point p, struct rect r)
{
	return p.x >= r.pt1.x && p.x < r.pt2.x
		&& p.y >= r.pt1.y && p.y < r.pt2.y;
}

// canonrect: 将矩形的坐标规范化
struct rect canonrect(struct rect r)
{
	struct rect temp;
	temp.pt1.x = min(r.pt1.x, r.pt2.x);
	temp.pt1.y = min(r.pt1.y, r.pt2.y);
	temp.pt2.x = max(r.pt1.x, r.pt2.x);
	temp.pt2.y = max(r.pt1.y, r.pt2.y);
	return temp;
}

int main()
{
	struct rect screen;
	struct point middle;
	screen.pt1 = makepoint(0, 0);
	screen.pt2 = makepoint(XMAX, XMAX);
	middle = makepoint((screen.pt1.x + screen.pt2.x)/2,
			(screen.pt1.y + screen.pt2.y)/2);
	printf("%d %d\n", middle.x, middle.y);

	struct point p3;
	p3 = addpoint(screen.pt1, screen.pt2);
	printf("%d %d\n", p3.x, p3.y);
	
	struct point *pp = &middle;
	printf("%d %d\n", (*pp).x, (*pp).y);
	pp->x = 33;
	printf("%d %d\n", pp->x, pp->y);
	return 0;
}

