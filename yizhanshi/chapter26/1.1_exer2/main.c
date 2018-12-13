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

    p = dequeue();
    free_node(p);

    p = dequeue();
    free_node(p);

    p = make_node(2);
    enqueue(p);
    p = make_node(3);
    enqueue(p);

    p = dequeue();
    free_node(p);

    p = make_node(4);
    enqueue(p);
    traverse(print_item);
    printf("**********************\n");

    p = search(3);
    delete(p);
    free_node(p);
    traverse(print_item);
    destroy();
	return 0;
}

