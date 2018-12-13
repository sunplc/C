#include <stdio.h>
#include "linkedlist.h"

void print_item(link p)
{
    printf("%d\n", p->item);
}

int main(void)
{
	link p = make_node(10);
    insert(p);
    p = make_node(5);
    insert(p);
    //traverse(print_item);
    //return 0;
    p = make_node(99);
    insert(p);
    p = make_node(7);
    insert(p);
    p = make_node(111);
    insert(p);

    p = search(5);
    delete(p);
    free_node(p);
    traverse(print_item);
    destroy();
    printf("*****\n");
    traverse(print_item);
    printf("*****\n");

    p = make_node(253);
    push(p);
    p = make_node(255);
    push(p);
    p = make_node(254);
    push(p);
    p = make_node(252);
    push(p);
    
    while((p = pop())) {
        print_item(p); 
        free_node(p);
    }

	return 0;
}

