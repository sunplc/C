#include <stdio.h>

int main(int argc, char *argv[])
{
	// const 向右结合，修饰它右边最近的变量或指针。
	// test const char **p; 指向一个指向不允许通过指针改写的字符变量的指针的指针
	char c = 'K';
	printf("%p\n", &c);

	const char *pc = &c;
	//c = 'T'; // Correct
	//*pc = 'X'; // Error
	//++pc; // Correct
	//char **ppc = &pc; // Error
	const char **ppc = &pc;

	c = 'F';
	printf("%p\n", &c);

	printf("%p %p %p %p\n", &c, pc, &pc, ppc);
	printf("****************************\n");
	
	// test char *const *p;
	char c2 = 'B';
	char *pc2 = &c2;
	char *const *ppc2 = &pc2;
	c2 = 'E';
	pc2 = &c2; // Correct
	//*ppc2 = pc2; // Error , so *ppc2 is read-only location
	ppc2 = &pc2; // Correct
	**ppc2 = 'M';
	printf("%c\n", c2);

	//test char **const p;
	const char c3 = 'U';
	char *const pc3 = &c3; // Initialization discards 'const' qualifier from pointer target type. const 初始器丢弃了const修饰符. 
	char **const ppc3 = &pc3; // Initialization discards 'const' qualifier from pointer target type

//	char c3 = 'U';
//	char *pc3 = &c3;
//	char **const ppc3 = &pc3; 
//	c3 = 'P';
//	pc3 = &c3;
//	**ppc3 = 'G';
//	printf("%c\n", **ppc3);

	return 0;
}

