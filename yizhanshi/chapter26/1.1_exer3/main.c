#include <stdio.h>
#include "linkedlist.h"

void print_item(link p)
{
    printf("%d\n", p->item);
}

int main(void)
{
	link p = make_node(1);
    enqueue(p);
    p = make_node(2);
    enqueue(p);
    p = make_node(3);
    enqueue(p);
    p = make_node(4);
    enqueue(p);
    p = make_node(5);
    enqueue(p);
    traverse(print_item);
    printf("******** reversed **************\n");

//    p = search(3);
//    delete(p);
//    free_node(p);
    //reverse_old();
    reverse();
    traverse(print_item);
    destroy();
	return 0;
}

