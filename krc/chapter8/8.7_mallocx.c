/*
 * 8.7 实例————存储分配程序
 */

// 最受限的类型就是指基本数据类型中最大的那个类型，
// 在某些机器中，最受限类型是double，而在另一些机器中则是int或long，
// 这里暂时将long类型作为内存块对齐时最受限的类型。
// 联合体的大小取决于最大元素的大小，
// 那么header的大小将大于或等于Align的大小，
// Align永远不会被使用，它仅仅用于强制每个头部在最坏的情况下满足对齐要求

#include <stdio.h>

typedef long Align;

union header {
	struct {
		union header *ptr;	// 下一个block的地址
		unsigned size;		// block的实际大小
	} s;
	Align x;
};

typedef union header Header;

static Header base;				// 空闲的内存块的地址链表的头（起始地址）
static Header *freep = NULL;	// 上一个找到空闲块的地方

void *mallocx(unsigned nbytes);
static Header *morecore(unsigned nu);
void freex(void *ap);
void *callocx(unsigned n, unsigned size);

// malloc: general-purpose storage allocator 通用内存分配器
void *mallocx(unsigned nbytes)
{
	// 检查需要分配的nbytes是否合法
	if (nbytes <= 0)
		return NULL;

	unsigned nunits;
	
	// 计算需要多少个Header大小的内存单元。
	// 将nbytes先减一之后除以header的大小，然后加一，
	// 相当于整除时不加一，有余数时加一。
	nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;
	//printf("需要分配nbytes = %u字节, nunits = %u\n", nbytes, nunits);

	Header *p, *prevp;
	// freep等于NULL，则表示从未申请过内存
	if ((prevp = freep) == NULL) {
		base.s.ptr = freep = prevp = &base;
		base.s.size = 0;
	}

	// 从freep的下一个内存块开始遍历
	for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
		if (p->s.size >= nunits) {		// 若空间足够大
			if (p->s.size == nunits)	// 若空间大小等于需要分配的大小，则从链表中删除节点p
				prevp->s.ptr = p->s.ptr;
			else {	// 若空间大小大于需要分配的大小，则返回p的尾部（高地址的部分）并将p的size减小
				p->s.size -= nunits;
				p += p->s.size;
				p->s.size = nunits;
			}
			freep = prevp;		// 将freep指向空闲内存块的上一个块
			return (void *) (p + 1);
		}

		// 若在链表中循环了一遍还没有找到足够大的内存块，则申请新内存
		if (p == freep)
			if ((p = morecore(nunits)) == NULL)
				return NULL;
	}
}

#define NALLOC 1024		// 内存申请的最小单位数

// morecore: ask system for more memory
static Header *morecore(unsigned nu)
{
	if (nu < NALLOC)
		nu = NALLOC;

	char *cp, *sbrk(int);
	Header *up;

	// brk, sbrk 是unix系统函数，用来申请内存块
	cp = sbrk(nu * sizeof(Header));
	printf("分配了 %lu 字节，起始地址 = %p\n", nu * sizeof(Header), cp);
	if (cp == (char *) -1) // 若没有空间
		return NULL;

	//格式化该内存块头部
	up = (Header *) cp;
	up->s.size = nu;

	// 将新申请的内存放入空闲列表
	freex((void *) (up + 1));
	return freep;
}

// free: put block ap in free list
// 将内存块ap计入空闲内存块列表中
void freex(void *ap)
{
	Header *bp, *p;

	// 返回给用户的是内存块中可使用的地址，减一是要让其指向内存块的头部
	bp = (Header *)ap - 1;
	// 检查bp的长度是否合法
	if (bp->s.size <= 0)
		return;

	// 从freep开始循环遍历列表
	for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
		// 情况一：p == p->s.ptr 表示列表只有base一个单元；
		// 情况二：p > p->s.ptr 表示p是列表最后一个元素，
		// p的下一个元素是列表第一个元素，
		// 只有这样才能满足p > p->s.ptr；
		// bp > p || bp < p->s.ptr 表示当符合情况二时，
		// bp不在p->s.ptr 与 p 的地址之间；
		// 当符合情况一时，p等于p->s.ptr，所以bp肯定不在p与p->s.ptr之间。
		if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
			break;

	// 若bp的尾部与p的下一个节点相邻，则将bp向上与p->s.ptr合并
	if (bp + bp->s.size == p->s.ptr) {
		bp->s.size += p->s.ptr->s.size;
		bp->s.ptr = p->s.ptr->s.ptr;
	} else
		bp->s.ptr = p->s.ptr;

	// 若bp的头部与p相邻，则将bp向下与p合并
	if (p + p->s.size == bp) {
		p->s.size += bp->s.size;
		p->s.ptr = bp->s.ptr;
	} else
		p->s.ptr = bp;
	
	freep = p; // 将freep指向空闲内存块的上一个块
}

// 练习 8-6 通过调用或修改 malloc 来实现 calloc 函数
void *callocx(unsigned n, unsigned size)
{
	size = n * size;
	char *p = (char *) mallocx(size);
	if (p == NULL)
		return NULL;
	else {
		char *tmp = p;
		while (size-- > 0) {
			*tmp++ = 0;
		}
		return p;
	}
}

// 练习 8-8 编写函数 bfree(p, n)，释放一个包含n个字符的的任意块p，
// 并将它放入由malloc 和 free 函数维护的空闲块链表中。
// 通过使用 bfree 函数，用户可以在任意时刻向空闲块链表中添加一个
// 静态或外部数组
void bfree(void *ap, unsigned nbytes)
{
	if (nbytes <= 0)
		return;

	// 计算nbytes最多可以存放多少个Header单元
	unsigned nunits = nbytes / sizeof(Header);
	if (nunits < 1)
		return;

	Header *bp;
	bp = (Header *) ap;
	bp->s.size = nunits;

	Header *p;
	// freep等于NULL，则表示从未申请过内存
	if ((p= freep) == NULL) {
		base.s.ptr = freep = p = &base;
		base.s.size = 0;
	}

	for (/*p = freep*/; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
		if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
			break;

	// 若bp的尾部与p的下一个节点相邻，则将bp向上与p->s.ptr合并
	if (bp + bp->s.size == p->s.ptr) {
		bp->s.size += p->s.ptr->s.size;
		bp->s.ptr = p->s.ptr->s.ptr;
	} else
		bp->s.ptr = p->s.ptr;

	// 若bp的头部与p相邻，则将bp向下与p合并
	if (p + p->s.size == bp) {
		p->s.size += bp->s.size;
		p->s.ptr = bp->s.ptr;
	} else
		p->s.ptr = bp;
	
	freep = p; // 将freep指向空闲内存块的上一个块
}

// 打印空闲块链表
void printList(void)
{
	Header *p;
	int i;
	puts("###### list ######");
	for (/*p = &base*/ p = freep, i = 0; p != NULL ; p = p->s.ptr, i++) {
		printf(" list[%d]: %p size = %u\n", i, p, p->s.size);
		if (p->s.ptr == freep /* p->s.ptr == &base */)
			break;
	}
	puts("##################");
}

int main(int argc, char *argv[])
{
	//printf("sizeof(Align) = %lu\n", sizeof(Align));
	//printf("sizeof(Header) = %lu\n", sizeof(Header));

	// 测试 mallocx 和  freex 函数
	//Header *p;
	//p = mallocx(1024);
	//printf("p = %p\n", p);
	//freex(p);

	//p = mallocx(16 * 2);
	//printf("p = %p\n", p);
	//freex(p);

	//p = mallocx(1024 * 3);
	//printf("p = %p\n", p);
	//freex(p);

	// 测试 callocx 函数
	//int *pi;
	//pi = (int *) callocx(2, 4);
	//printf("%p %d\n", pi, *pi);

	// 静态变量或外部变量存储在低地址的 data segment，
	// 也可以将其内存回收放入链表再使用，测试bfree函数
	static char str[500];
	printf("str = %p\n", str);
	bfree(str, 500);

	static char str2[500];
	printf("str2 = %p\n", str2);
	bfree(str2, 500);

	static char str3[500];
	printf("str3 = %p\n", str3);
	bfree(str3, 500);

	printList();

	return 0;
}

