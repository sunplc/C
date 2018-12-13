#include <stdlib.h>
#include <stdio.h>
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
    for (p = head; p; p = p->next) {
        visit(p);
        //printf("p=%p, next=%p\n", p, p->next);
    }
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
    // when queue is empty
    if (head == NULL)
        return NULL;
    else {
        link p = head;
        // when head and tail pointed same node, that's mean this queue has only one node
        if (head == tail) {
            head = tail = NULL;
        } else
            head = head->next;
        return p;
    }
}

void reverse_old(void)
{
    if (head == NULL || head == tail)
        return;

    link new_head = NULL;
    link current = NULL;
    link p, n;
    int length = 0;
    for (p = head; p; p = p->next) {
        ++length;
    }
    for (; length > 0; length--) {
        for (p = head; p; p = p->next) {
            if (head->next == NULL)
                n = p;
            else
                n = p->next;
            if (n != NULL && n->next == NULL) {
                //printf("item=%d,p=%p\n", n->item, n);
                if (new_head == NULL) {
                    new_head = n;
                    current = n;
                } else {
                    current->next = n;
                    current = n;
                }
                p->next = NULL;
            } 
        }
    }
    head = new_head;
    tail = current;
}

void reverse(void)
{
    if (head == NULL || head == tail)
        return;
    link curr, prev = NULL, next;
    for (curr = head; curr; curr = next) {
        if (prev == NULL)
            tail = curr;
        next = curr->next;
        curr->next = prev;
        prev = curr;     
    }
    head = prev;
}
