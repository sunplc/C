#include <stdlib.h>
#include "linkedlist.h"

static link head = NULL;
static link tail = NULL;

link make_node(unsigned char item)
{
    link p = malloc(sizeof(*p));
    p->item = item;
    p->next = NULL;
    return p;
}

void free_node(link p)
{
    if (p == NULL)
        return;
    free(p);
}

link search(unsigned char key)
{
    link p;
    for (p = head; p; p = p->next)
        if (p->item == key)
            return p;
    return NULL;
}

//排序插入，从小到大
void insert(link p)
{
    //p->next = head;
    //head = p;
    if (head == NULL) {
        p->next = head;
        head = p;
    } else {
        link now;
        for (now = head; now; now = now->next) {
            if (p->item <= now->item)
                break;
        }
        if (now == head) {
            p->next = head;
            head = p; 
        } else {
            link pre;
            for (pre = head; pre; pre = pre->next) {
                if (pre->next == now) {
                    pre->next = p;
                    p->next = now;
                }
            }
        }
    }
}

void delete(link p)
{
    if (p == NULL)
        return;
    link pre;
    if (p == head) {
        head = p->next; 
        return;
    }
    for (pre = head; pre; pre = pre->next)
        if (pre->next == p) {
            pre->next = p->next;
            return;
        }
}

void traverse(void (*visit)(link))
{
    link p;
    for (p = head; p; p = p->next)
        visit(p);
}

void destroy(void)
{
    link q, p = head;
    head = NULL;
    while (p) {
        q = p;
        p = p->next;
        free_node(q);
    }
}

void push(link p)
{
    insert(p);
}

link pop(void)
{
    if (head == NULL) {
        return NULL; 
    } else {
        link p = head;
        head = head->next;
        return p;
    }
}

void enqueue(link p)
{
    if (tail == NULL) {
        tail = p;
        head = p;
    } else {
        tail->next = p; 
        tail = p;
    }
}

link dequeue(void)
{
    // 队列为空时
    if (head == NULL)
        return NULL;
    else {
        link p = head;
        // 头和尾指向同一个节点，即队列只有一个节点时
        if (head == tail) {
            head = tail = NULL;
        } else
            head = head->next;
        return p;
    }
}

