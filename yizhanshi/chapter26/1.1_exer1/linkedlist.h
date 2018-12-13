#ifndef LINKEDLIST_H
#define LINKEDLIST_H
struct node {
	unsigned char item;
	struct node *next;
};
typedef struct node *link;

link make_node(unsigned char item);
void free_node(link p);
link search(unsigned char item);
void insert(link p);
void delete(link p);
void traverse(void (*visit) (link));
void destroy(void);
void push(link p);
link pop(void);

#endif
