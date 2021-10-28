
/*
 * 将 汇编代码文件 与 c文件 一起编译
 * gcc 3.73.c 3.73.s -o 3.73.out
 *
 */
#include <stdio.h>
#include <assert.h>

// 这个函数原型声明是必不可少的，否则会出错,
// 在这卡了很久才找到原因是缺少函数原型声明
int find_range_asm(float);

typedef enum {NEG, ZERO, POS, OTHER} range_t;

int main(void)
{
    puts("Input an float number:");
    float x;
    scanf("%f", &x);
    printf("x = %f\n", x);

    printf("result of find_range_asm = %d\n",
            find_range_asm(x));


    assert(OTHER == find_range_asm(0.0/0.0));
    assert(NEG == find_range_asm(-2.3));
    assert(ZERO == find_range_asm(0.0));
    assert(POS == find_range_asm(3.33));
    return 0;
}

