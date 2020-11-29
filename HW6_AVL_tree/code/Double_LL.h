#ifndef DOUBLE_LL_H
#define DOUBLE_LL_H
// #define DEBUG_DOUBLE_LL_H

#include <stdio.h>
#include <stdlib.h>

// Element is link list
typedef struct Node_tr
{
    struct Node_tr *left;
    struct Node_tr *right;
    char name[21];  // key
    char phone[11]; // value
    // AVL tree parameters
    int height;
    int bf; // balance factor
} Node_tr;

typedef struct Node
{
    struct Node *next;
    struct Node *prev;
    Node_tr *np_tr;
} Node;

typedef struct LinkList
{
    Node *head;
    Node *tail;
} LinkList;

void printLL(LinkList *lp, int order) // order=0: sequential, order=1: reverse
{
    if (!lp)
    {
        fprintf(stderr, "printLL(): invalid Link List\n");
        exit(EXIT_FAILURE);
    }
    if (!lp->head)
    {
        fprintf(stdout, "printLL(): empty Link List\n");
        return;
    }
    if (order == 0)
    {
        for (Node *np = lp->head; np->next; np = np->next)
            printf("%s -> ", np->np_tr->name);
        printf("%s\n", lp->tail->np_tr->name);
    }
    else
    {
        for (Node *np = lp->tail; np->prev; np = np->prev)
            printf("%s <- ", np->np_tr->name);
        printf("%s\n", lp->head->np_tr->name);
    }
}

LinkList *create_ll()
{
    LinkList *lp = (LinkList *)calloc(1, sizeof(LinkList));
    if (!lp) // p == NULL
    {
        fprintf(stderr, "create_ll(): Out of memory!\n");
        exit(EXIT_FAILURE);
    }
    return lp;
}

Node *create_node(Node_tr *np_tr)
{
    Node *np = (Node *)malloc(sizeof(Node));
    if (!np) // p == NULL
    {
        fprintf(stderr, "create_node(): Out of memory!\n");
        exit(EXIT_FAILURE);
    }
    np->np_tr = np_tr;
    np->next = np->prev = NULL;
    return np;
}

void push_node(LinkList *lp, Node *np) // Inserts the node on the back of the link list.
{
    // Check input is valid
    if (!lp)
    {
        fprintf(stderr, "push_node(): invalid Link List\n");
        exit(EXIT_FAILURE);
    }
    if (!np || np->prev || np->next)
    {
        fprintf(stderr, "push_node(): invalid Node (Empty or belongs to another Link List)\n");
        exit(EXIT_FAILURE);
    }
    // When ll is empty
    if (!lp->head)
        lp->tail = lp->head = np;
    else
    {
        np->next = NULL;
        lp->tail->next = np;
        np->prev = lp->tail;
        lp->tail = np;
    }
#ifdef DEBUG_DOUBLE_LL_H
    printf("push(%d):\n", np->val);
    printLL(lp, 0);
#endif
}

void push_front_node(LinkList *lp, Node *np) // Inserts the node at the front of the link list.
{
    // Check the input is valid
    if (!lp)
    {
        fprintf(stderr, "push_node(): invalid Link List\n");
        exit(EXIT_FAILURE);
    }
    if (!np || np->prev || np->next)
    {
        fprintf(stderr, "push_node(): invalid Node (Empty or belongs to another Link List)\n");
        exit(EXIT_FAILURE);
    }
    // When ll is empty
    if (!lp->head)
        lp->tail = lp->head = np;
    else
    {
        np->prev = NULL;
        lp->head->prev = np;
        np->next = lp->head;
        lp->head = np;
    }
#ifdef DEBUG_DOUBLE_LL_H
    printf("enqueue(%d):\n", np->val);
    printLL(lp, 0);
#endif
}

Node_tr *pop_node(LinkList *lp) // Remove the last node in link list
{
    // Check the input is valid
    if (!lp)
    {
        fprintf(stderr, "pop_node(): invalid Link List!\n");
        exit(EXIT_FAILURE);
    }
    // When ll is empty
    if (!lp->head)
    {
        fprintf(stderr, "pop_node(): Link List is empty.");
        exit(EXIT_FAILURE);
    }
    Node_tr *np_tr = lp->tail->np_tr;
    Node *new_tail = lp->tail->prev;
    // When only one node left: new_tail == NULL
    if (!new_tail)
        lp->head = NULL;
    else
        new_tail->next = NULL;
    free(lp->tail);
    lp->tail = new_tail;
#ifdef DEBUG_DOUBLE_LL_H
    printf("pop(): %d\n", np_tr->key);
    printLL(lp, 0);
#endif
    return np_tr;
}

Node_tr *pop_front_node(LinkList *lp) // Remove the first node in link list
{
    // Check the input is valid
    if (!lp)
    {
        fprintf(stderr, "pop_node(): invalid Link List!\n");
        exit(EXIT_FAILURE);
    }
    // When ll is empty
    if (!lp->head)
    {
        fprintf(stderr, "dequeue_node(): Link List is empty.");
        exit(EXIT_FAILURE);
    }
    Node_tr *np_tr = lp->head->np_tr;
    Node *new_head = lp->head->next;
    // When only one node left: new_head == NULL
    if (!new_head)
        lp->head = NULL;
    else
        new_head->prev = NULL;
    free(lp->head);
    lp->head = new_head;
#ifdef DEBUG_DOUBLE_LL_H
    printf("dequeue(): %d\n", np_tr->val);
    key
        printLL(lp, 0);
#endif
    return np_tr;
}

void free_LL(LinkList *lp) // Free all nodes in the link list
{
    if (!lp)
    {
        fprintf(stderr, "printLL(): invalid Link List\n");
        return;
    }
    int i = 0;
    while (lp->head)
    {
        pop_node(lp);
        ++i;
    }
    fprintf(stderr, "delete %d node%c.\n", i, i <= 1 ? '\0' : 's');
}

#endif // DOUBLE_LL_H