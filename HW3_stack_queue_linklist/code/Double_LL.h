#ifndef DOUBLE_LL_H
#define DOUBLE_LL_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    struct Node *next;
    struct Node *prev;
    int val;
} Node;

typedef struct LinkList
{
    Node *head;
    Node *tail;
} LinkList;

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

void printLL(LinkList *lp, int mode) // mode=0: ordered, mode=1: reverse
{
    // Invalid Link List
    if (!lp)
    {
        fprintf(stderr, "printLL(): invalid Link List\n");
        return;
    }
    if (!lp->head)
    {
        fprintf(stderr, "printLL(): empty Link List\n");
        return;
    }
    if (mode == 0)
    {
        for (Node *np = lp->head; np->next; np = np->next)
            printf("%3d -> ", np->val);
        printf("%3d\n", lp->tail->val);
    }
    else
    {
        for (Node *np = lp->tail; np->prev; np = np->prev)
            printf("%3d <- ", np->val);
        printf("%3d\n", lp->head->val);
    }
}

Node *create_node(int val)
{
    Node *np = (Node *)malloc(sizeof(Node));
    if (!np) // p == NULL
    {
        fprintf(stderr, "create_node(): Out of memory!\n");
        exit(EXIT_FAILURE);
    }
    np->val = val;
    np->next = np->prev = NULL;
    return np;
}

void push_node(LinkList *lp, Node *np)
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
#ifdef DEBUG
    printf("push(%d):\n", np->val);
    printLL(lp, 0);
#endif
}

void enqueue_node(LinkList *lp, Node *np)
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
#ifdef DEBUG
    printf("enqueue(%d):\n", np->val);
    printLL(lp, 0);
#endif
}

void pop_node(LinkList *lp) // Remove the last node in link list
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
        return;
    }
    Node *new_tail = lp->tail->prev;
    // When only one node left: new_tail == NULL
    if (!new_tail)
    {
        puts("pop_node(): One node left.");
        lp->head = NULL;
    }
    else
        new_tail->next = NULL;
    free(lp->tail);
    lp->tail = new_tail;
#ifdef DEBUG
    puts("pop():");
    printLL(lp, 0);
#endif
}

void dequeue_node(LinkList *lp) // Remove the last node in link list
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
        return;
    }
    Node *new_tail = lp->tail->prev;
    // When only one node left: new_tail == NULL
    if (!new_tail)
    {
        puts("pop_node(): One node left.");
        lp->head = NULL;
    }
    else
        new_tail->next = NULL;
    free(lp->tail);
    lp->tail = new_tail;
#ifdef DEBUG
    puts("pop():");
    printLL(lp, 0);
#endif
}

#endif // DOUBLE_LL_H