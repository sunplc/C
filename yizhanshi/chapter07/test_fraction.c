#include <stdio.h>
#include <math.h>

/* 求两个整数的最大公约数 */
int greatest_common_divisor(int a, int b)
{
	if (a % b == 0)
		return b;
	else
		return greatest_common_divisor(b, a % b);
}

/* 求两个整数的最小公倍数  */
int least_common_multiple(int a, int b)
{
	int c = greatest_common_divisor(a, b);
	if (c == 1)
		return a * b;
	else
		return a * b / c;
}

// 声明分数的结构体
struct rational {
	int a, b;
};

// 获取分子
int numerator_part(struct rational r)
{
	return r.a;
}

// 获取分母
int denominator_part(struct rational r)
{
	return r.b;
}

// 定义一个分数结构体并返回
struct rational make_rational(int a, int b)
{
	if (a == 0 || b == 0) {
		a = 0;
		b = 0;
	} else if (b < 0) {
		a = -a;
		b = -b;
	}
	// 判断分子分母是否能约分
	int gcd = greatest_common_divisor(a, b);
	if (gcd != 1) {
		if (gcd < 0)
			gcd = -gcd;
		a = a / gcd;
		b = b / gcd;
	}
	struct rational r;
	r.a = a;
	r.b = b;
	return r;
}

// 打印分数rational结构体
void print_rational(struct rational r)
{
	int a = numerator_part(r), b = denominator_part(r);
	printf("%d/%d\n", a, b);
}

// 两分数相加
struct rational add_rational(struct rational r1, struct rational r2)
{
	int r1_a = numerator_part(r1), r1_b = denominator_part(r1),
	r2_a = numerator_part(r2), r2_b = denominator_part(r2);
	// 算出两个分母的最小公倍数
	int lcm = least_common_multiple(r1_b, r2_b);
	int a = r1_a * (lcm / r1_b) + r2_a * (lcm / r2_b);
	int b = lcm;
	struct rational r = make_rational(a, b); 
	return r;
}

// 两分数相减
struct rational sub_rational(struct rational r1, struct rational r2)
{
	int r1_a = numerator_part(r1), r1_b = denominator_part(r1),
	r2_a = numerator_part(r2), r2_b = denominator_part(r2);
	// 算出两个分母的最小公倍数
	int lcm = least_common_multiple(r1_b, r2_b);
	int a = r1_a * (lcm / r1_b) - r2_a * (lcm / r2_b);
	int b = lcm;
	struct rational r = make_rational(a, b); 
	return r;	
}

// 两分数相乘
struct rational mul_rational(struct rational r1, struct rational r2)
{
	int r1_a = numerator_part(r1), r1_b = denominator_part(r1),
	r2_a = numerator_part(r2), r2_b = denominator_part(r2);
	int a = r1_a * r2_a;
	int b = r1_b * r2_b;
	struct rational r = make_rational(a, b); 
	return r;
}

// 两分数相除
struct rational div_rational(struct rational r1, struct rational r2)
{
	int r1_a = numerator_part(r1), r1_b = denominator_part(r1),
	r2_a = numerator_part(r2), r2_b = denominator_part(r2);
	int a = r1_a * r2_b;
	int b = r1_b * r2_a;
	struct rational r = make_rational(a, b); 
	return r;
}

int main(void)
{
	int a = 38, b = 12;
	printf("a = %d, b = %d\n", a, b);
	int c =	greatest_common_divisor(a, b);
	printf("the greatest common divisor is %d\n", c);
	int d = least_common_multiple(a, b);
	printf("the least common multiple is  %d\n", d);

	struct rational r1 = make_rational(3, 8);
	struct rational r2 = make_rational(2, -7); 
	printf("r1 = %d/%d, r2 = %d/%d\n", r1.a, r1.b, r2.a, r2.b);
	
	print_rational(add_rational(r1, r2));
	print_rational(sub_rational(r1, r2));
	print_rational(mul_rational(r1, r2));
	print_rational(div_rational(r1, r2));
	return 0;
}
