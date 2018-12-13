#include <stdio.h>

// 检查当前机器是大端字节序还是小端字节序
void check_endian(void)
{
	unsigned int ui = 1;
	char *pc = (char *) &ui;
	if (*pc) {
		puts("Little endian");
	} else {
		puts("Big endian");
	}
}

// 将指定的多个字节当作字符数组，把每个字节用十六进制打印出来
void show_mem_rep(char *start, int n)
{
	int i;
	for (i = 0; i < n; i++) {
		printf("byte %d: \t %p \t %.2x\n", i, &start[i], start[i]);
	}
	putchar('\n');
}

int a=0x12, b=0x3456, c=0x11223344;

// 在小端字节序机器中，多字节的数据类型的二进制表示的最后的字节先存储
// 例如：int a = 0x12345678, 变量 a 被分配4个字节，
// a的起始地址(&a),是低地址,后续还有3个字节从低到高的分布
// 78 存放在从低到高的第一个字节，56、34、12 分别放在第二、三、四个字节
// 所以，在小端机器中，数据类型的高位放在高地址，低位放在低地址
//
// 而在大端字节序机器中，多字节的数据类型的二进制表示的最先的字节先存储
// 即如上例，12、34、56、78 分别存放在第一、二、三、四个字节中
// 所以，在大端机器中，数据类型的高位放在低地址，低位放在高地址
// 
// 无论是在大端还是小段，数组、结构体、联合体的的字节存储顺序总是：
// 最先的字节在低地址，最后的字节在高地址。
// ？？？
// 
int main(int argc, char *argv[])
{
    unsigned char arr[2] = {0x01, 0x00};
    unsigned  int x = * (unsigned short int *) arr;
	// 在小端字节序机器上输出1，大端上输出256
    printf("%d\n", x);

    // 字符串属于数组，
    // 而大端或小端机器上的存储顺序不同，似乎仅仅体现在 整型和浮点型上
	char str[] = "abcd";    // a b c d 转化成 int 的十六进制表示分别是 61 62 63 64
	show_mem_rep(str, 4);

    int q = 0x01020304;
	show_mem_rep((char *)(&q), 4);

	check_endian();

	printf("-------------------- \n");



    puts("a b c 是三个全局变量，存储在 .data 段，位于低地址");
	printf("a = 0x%x, &a=%p\n", a, &a);
	show_mem_rep((char *)&a, sizeof(a));

	printf("b = 0x%x, &b=%p\n", b, &b);
	show_mem_rep((char *)&b, sizeof(b));

	printf("c = 0x%x, &c=%p\n", c, &c);
	show_mem_rep((char *)&c, sizeof(c));

    puts("i j k 是三个局部变量(自动变量)，程序运行时在 栈 中实时分配，位于高地址");
	int i=0x12, j=0x2345, k=0x34567811;

	printf("i = 0x%x, &i=%p\n", i, &i);
	show_mem_rep((char *)&i, sizeof(i));

	printf("j = 0x%x, &j=%p\n", j, &j);
	show_mem_rep((char *)&j, sizeof(j));

	printf("k = 0x%x, &k=%p\n", k, &k);
	show_mem_rep((char *)&k, sizeof(k));

	return 0;
}

