#ifndef DOUBLE_LL_H
#define DOUBLE_LL_H
// #define DEBUG_DOUBLE_LL_H
#include <stdio.h>
#include <stdlib.h>

typedef struct gnode
{
    int vertex;
    int weight;
    int edge_code; // A -> B: B.edge_code = E(A,B)
    struct gnode *link;
} gnode;

// vhead vertex
typedef struct vheadnode
{
    int count;
    gnode *link;
} vheadnode;

typedef struct graph
{
    vheadnode *vhead;
    int v_num;
    int v_start; // default = 0
} graph;

typedef struct Node
{
    struct Node *next;
    struct Node *prev;
    vheadnode *vhead;
} Node;

typedef struct LinkList
{
    Node *head;
    Node *tail;
} LinkList;

// order=0: sequential, order=1: reverse
void printLL(LinkList *lp, vheadnode *ref)
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
    for (Node *np = lp->head; np; np = np->next)
    {
        printf("v_%3d: %d", np->vhead - ref, np->vhead->count);
        if (np->vhead->link)
            printf(" -> %p", np->vhead->link);
        printf("\n");
    }
}

LinkList *create_ll()
{
    LinkList *lp = (LinkList *)calloc(1, sizeof(LinkList));
    if (!lp)
    {
        fprintf(stderr, "create_ll(): Out of memory!\n");
        exit(EXIT_FAILURE);
    }
    return lp;
}

Node *create_node(vheadnode *vhead)
{
    Node *np = (Node *)malloc(sizeof(Node));
    if (!np)
    {
        fprintf(stderr, "create_node(): Out of memory!\n");
        exit(EXIT_FAILURE);
    }
    np->vhead = vhead;
    np->next = np->prev = NULL;
    return np;
}

// Inserts the node on the back of the link list.
void push_back(LinkList *lp, Node *np)
{
    // Check input is valid
    if (!lp)
    {
        fprintf(stderr, "push_back(): invalid Link List\n");
        exit(EXIT_FAILURE);
    }
    if (!np || np->prev || np->next)
    {
        fprintf(stderr, "push_back(): invalid Node (Empty or belongs to another Link List)\n");
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

void push_front(LinkList *lp, Node *np) // Inserts the node at the front of the link list.
{
    // Check the input is valid
    if (!lp)
    {
        fprintf(stderr, "push_front(): invalid Link List\n");
        exit(EXIT_FAILURE);
    }
    if (!np || np->prev || np->next)
    {
        fprintf(stderr, "push_front(): invalid Node (Empty or belongs to another Link List)\n");
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

int LL_empty(LinkList *lp)
{
    return lp->head == NULL;
}

// Remove the last node in link list
vheadnode *pop_back(LinkList *lp)
{
    // Check the input is valid
    if (!lp)
    {
        fprintf(stderr, "pop_back(): invalid Link List!\n");
        exit(EXIT_FAILURE);
    }
    // When ll is empty
    if (!lp->head)
    {
        fprintf(stderr, "pop_back(): Link List is empty.");
        exit(EXIT_FAILURE);
    }
    vheadnode *vhead = lp->tail->vhead;
    Node *new_tail = lp->tail->prev;
    // When only one node left: new_tail == NULL
    if (!new_tail)
        lp->head = NULL;
    else
        new_tail->next = NULL;
    free(lp->tail);
    lp->tail = new_tail;
#ifdef DEBUG_DOUBLE_LL_H
    printf("pop(): ");
    print_gnode(gnd);
    printLL(lp, 0);
#endif
    return vhead;
}

// Remove the first node in link list
vheadnode *pop_front(LinkList *lp)
{
    // Check the input is valid
    if (!lp)
    {
        fprintf(stderr, "pop_front(): invalid Link List!\n");
        exit(EXIT_FAILURE);
    }
    // When ll is empty
    if (!lp->head)
    {
        fprintf(stderr, "pop_front(): Link List is empty.");
        exit(EXIT_FAILURE);
    }
    vheadnode *vhead = lp->head->vhead;
    Node *new_head = lp->head->next;
    // When only one node left: new_head == NULL
    if (!new_head)
        lp->head = NULL;
    else
        new_head->prev = NULL;
    free(lp->head);
    lp->head = new_head;
#ifdef DEBUG_DOUBLE_LL_H
    printf("pop_front(): ");
    print_gnode(gnd);
    printLL(lp, 0);
#endif
    return vhead;
}

// Free all nodes in the link list
void free_LL(LinkList *lp)
{
    if (!lp)
    {
        fprintf(stderr, "printLL(): invalid Link List\n");
        return;
    }
    int i = 0;
    while (lp->head)
    {
        pop_back(lp);
        ++i;
    }
    fprintf(stderr, "delete %d node%s.\n", i, i <= 1 ? "" : "s");
}

#endif // DOUBLE_LL_H