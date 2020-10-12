#ifndef QUEUE_H
#define QUEUE_H
#include <stdio.h>
#include <stdlib.h>
// Actual capacity: QUEUE_MAX-1
#define QUEUE_MAX 100

typedef struct
{
    int queue[QUEUE_MAX];
    int front; // No element
    int rear;  // Element exits after first enque
} Queue;

Queue *new_Queue()
{
    Queue *p = (Queue *)calloc(1, sizeof(Queue));
    p->rear = p->front = QUEUE_MAX - 1;
    return p;
}

int isQEmpty(const Queue *self)
{
    return self->front == self->rear;
}

void printQ(const Queue *self)
{
    if (isQEmpty(self))
    {
        printf("Queue is empty. front: %d rear: %d\n", self->front, self->rear);
        return;
    }
    // printf("front: %d rear: %d\n", self->front, self->rear);
    for (int i = self->rear;
         i != self->front;
         i = (i == 0 ? QUEUE_MAX - 1 : i - 1))
        printf("%3d", self->queue[i]);
    printf("\n");
}

int front(const Queue *self)
{
    if (isQEmpty(self))
    {
        fprintf(stderr, "Err front(): Queue is empty\n");
        exit(EXIT_FAILURE);
        return -1;
    }
    else
    {
        return self->queue[(self->front + 1) % QUEUE_MAX];
    }
}

int rear(const Queue *self)
{
    if (isQEmpty(self))
    {
        fprintf(stderr, "Err rear(): Queue is empty\n");
        exit(EXIT_FAILURE);
    }
    return self->queue[self->rear];
}

void enqueue(Queue *self, const int x)
{
    // Queue is full
    if ((self->rear + 1) % QUEUE_MAX == self->front)
    {
        fprintf(stderr, "Err enqueue(): Queue is full\n");
        exit(EXIT_FAILURE);
    }
    self->rear = (self->rear + 1) % QUEUE_MAX;
    self->queue[self->rear] = x;
}

int dequeue(Queue *self)
{
    if (isQEmpty(self))
    {
        fprintf(stderr, "Err rear(): Queue is empty\n");
        exit(EXIT_FAILURE);
    }
    self->front = (self->front + 1) % QUEUE_MAX;
    return self->queue[self->front];
}

#endif // QUEUE_H