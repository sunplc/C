/**
 * 商品管理系统
 *
 * 这里仅测试将单链表存入文件 和 从文件中读取出单链表的实现
 */

#include <stdio.h>
#include <stdlib.h>

#define DAT_FILE "sale.dat"

struct commodity
{
	int id;
	char name[24];
	float price;
	int saled_amount;
	int stock_amount;
};

struct linkedlist
{
	struct commodity comm;
	struct linkedlist *next;
};

int main(void)
{

	struct linkedlist *head;

	struct linkedlist ll6 = {{6, "水果", 34.8, 10, 20}, NULL};
	struct linkedlist ll5 = {{5, "衣服", 34.8, 10, 20}, &ll6};
	struct linkedlist ll4 = {{4, "笔记本", 4000.7, 10, 20}, &ll5};
	struct linkedlist ll3 = {{3, "笔", 3.2, 10, 20}, &ll4};
	struct linkedlist ll2 = {{2, "枪", 3000.3, 10, 20}, &ll3};
	struct linkedlist ll1 = {{1, "书籍", 96.5, 10, 20}, &ll2};
	int len = 6;

	head = &ll1;

	puts("\n------------- 写入链表到文件 -------------------\n");
	int i;
	for (i = 0; i < len; i++) {
		printf("%d\t%s\t%f\n", head->comm.id, head->comm.name, head->comm.price);
		head = head->next;
	}
	head = &ll1;

	// 将链表写入文件
    FILE *fp = fopen(DAT_FILE, "wb+");
    if (fp == NULL) {
        printf("打开数据文件失败\n");
        return 1;
    }
    
    long node_len = sizeof(struct linkedlist);

    fseek(fp, 0, SEEK_SET);

	for (i = 0; i < len; i++) {
	    if (fwrite(head, node_len, 1, fp) <= 0) {
	        break;
	    }

	    // printf(">>>> id=%d\n", head->comm.id);
		head = head->next;
	}

    fclose(fp);


    // 从文件中读取数据，加载链表
    fp = fopen(DAT_FILE, "rb");
    if (fp == NULL) {
        printf("打开数据文件失败\n");
        return 1;
    }

    //移动读写位置到 文件末尾之前的一个链表单位长度
    fseek(fp, node_len * -1, SEEK_END);

    struct linkedlist *tmp = NULL;

	for (i = 0; i < len; i++) {
		head = malloc(node_len);
	    
	    if (fread(head, node_len, 1, fp) <= 0) {
	        break;
	    }
	    // printf(">>>> id=%d\n", head->comm.id);

	    //由于读取了一个链表单位长度，读写位置向后移动了一个单位，所以此时要向前移动两个链表单位长度
	    fseek(fp, node_len * -2, SEEK_CUR);

	    head->next = tmp;
		tmp = head;
	}

    fclose(fp);

    puts("\n------------- 从文件读出链表 -------------------\n");
	for (i = 0; i < len; i++) {
		printf("%d\t%s\t%f\n", head->comm.id, head->comm.name, head->comm.price);
		head = head->next;
	}

	return 0;
}