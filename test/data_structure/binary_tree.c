/*************************************************************************
	> File Name: binary_tree.c
	> Author: 
	> Mail: 
	> Created Time: Fri 15 Jul 2016 08:28:42 PM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

typedef struct node {
    int val;
    struct node * left;
    struct node * right;
} node_t;

void insert(node_t * tree, int val);
void print_tree(node_t * current);
void printDFS(node_t * current);

int main()
{
    node_t * test_list = malloc(sizeof(node_t));
    insert(test_list, 5);
    insert(test_list, 89);
    insert(test_list, 4);
    insert(test_list, 42);
    insert(test_list, 3);
    //printDFS(test_list);
    print_tree(test_list);
    return 0;
}

void insert(node_t * tree, int val)
{
    if(tree->val == 0) {
        tree->val = val;
    } else if (val < tree->val) {
        if (tree->left != NULL)
            insert(tree->left, val);
        else {
            tree->left = malloc(sizeof(node_t));
            tree->left->val = val;
        }
    } else if (val >= tree->val) {
        if (tree->right != NULL)
            insert(tree->right, val);
        else {
            tree->right = malloc(sizeof(node_t));
            tree->right->val = val;
        }
    }
}

void print_tree(node_t * current)
{
    if (current != NULL) printf("\n%d ", current->val);
    if (current->left != NULL) printf("L-%d ", current->left->val);
    if (current->right != NULL) printf("R-%d ", current->right->val);
    if (current->left != NULL) print_tree(current->left);
    if (current->right != NULL) print_tree(current->right);
}

void printDFS(node_t * current)
{
    if (current->left != NULL) printDFS(current->left);
    if (current != NULL) printf("%d ", current->val);
    if (current->right != NULL) printDFS(current->right);
}
