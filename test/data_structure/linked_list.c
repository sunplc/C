/*************************************************************************
	> File Name: linked_list.c
	> Author: 
	> Mail: 
	> Created Time: Thu 14 Jul 2016 09:04:41 PM PDT
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node * next;
} node_t;

void print_list(node_t * head);
void push(node_t * head, int val);
int pop(node_t ** head);
int mypop(node_t * head);
void add(node_t ** head, int val);
int remove_last(node_t * head);
int remove_by_index(node_t ** head, int n);
void remove_list(node_t ** head);

int main()
{
    node_t * head = NULL;
    head = malloc(sizeof(node_t));
    if (head == NULL) {
        return 1;
    }

    head->val = 1;
    head->next = malloc(sizeof(node_t));
    head->next->val = 2;
    head->next->next = NULL;
    
    push(head, 3);
    push(head, 4);
  
    int first = pop(&head);
    printf("the poped value is %d\n", first);
    print_list(head);
    printf("************************************\n");
    add(&head, 1);
    int last = remove_last(head);
    printf("the removed last value is %d\n", last);
    printf("************************************\n");
    remove_by_index(&head, 0);
    print_list(head);
    remove_list(&head);
    printf("************ after remove_list ************\n");
    print_list(head);
    return 0;
}

// print the linked list 
void print_list(node_t * head)
{
    node_t * current = head;
    while (current != NULL) {
        printf("%d\n", current->val);
        current = current->next;
    }
}

// Pushing an item to the end of the list
void push(node_t * head, int val)
{
    node_t * current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = malloc(sizeof(node_t));
    current->next->val = val;
    current->next->next = NULL;
}

// Adding an item to the beginning of the list
void add(node_t ** head, int val)
{
    node_t * new_head = malloc(sizeof(node_t));

    new_head->val = val;
    new_head->next = *head;
    *head = new_head;
}

// Removing the first item of the list
int pop(node_t ** head)
{
   int retval = -1;
   node_t * next_node = NULL;

   if (*head == NULL) {
       return -1;
   }

   next_node = (*head)->next;
   retval = (*head)->val;
   free(*head);
   *head = next_node;
   return retval;
}

// Removing the last item of the list
int remove_last(node_t * head)
{
    int retval = 0;
    /* if there is only one item of the list, remove it */
    if (head->next == NULL) {
        retval = head->val;
        free(head);
        head = NULL;
        return retval;
    }

    node_t * current = head;
    while (current->next->next != NULL) {
        current = current->next;
    }

    retval = current->next->val;
    free(current->next);
    current->next = NULL;
    return retval;
}

// Removing a specific item
int remove_by_index(node_t ** head, int n)
{
    if (n == 0) {
        return pop(head);
    }
    int i;
    node_t * current = *head;
    for (i = 0; i < n-1; ++i) {
        if(current->next == NULL) {
            return -1;
        }
        current = current->next;
    }
    node_t * temp_node = current->next;
    int retval = current->val;
    current->next = temp_node->next;
    free(temp_node);
    return retval;
}

// Removing list
void remove_list(node_t ** head)
{
    node_t * current = *head, * next = *head;

    while (current) {
        next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}
