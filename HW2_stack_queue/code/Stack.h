#ifndef STACK_H
#define STACK_H
#include <stdio.h>
#include <stdlib.h>
#define STACK_MAX 100

typedef struct
{
    int stack[STACK_MAX];
    int top;
} Stack;

Stack *new_Stack()
{
    Stack *p = (Stack *)calloc(1, sizeof(Stack));
    p->top = -1;
    return p;
}

int isSEmpty(const Stack *self)
{
    return self->top == -1;
}

void printS(const Stack *self)
{
    if (isSEmpty(self))
    {
        printf("Stack is empty. top: %d\n", self->top);
        return;
    }
    // printf("top: %d\n", self->top);
    for (int i = 0; i <= self->top; ++i)
        printf("%3d", self->stack[i]);
    printf("\n");
}

int pop(Stack *self)
{
    if (isSEmpty(self))
    {
        fprintf(stderr, "Err pop(): Stack is empty\n");
        exit(EXIT_FAILURE);
    }
    return self->stack[self->top--];
}

void push(Stack *self, const int x)
{
    self->stack[++self->top] = x;
}

#endif // STACK_H