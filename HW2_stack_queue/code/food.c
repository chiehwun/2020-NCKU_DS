// #define DEBUG
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Stack.h"
#include "Queue.h"
FILE *openFile(const char *fileName, const char *mode);
void printALL(Stack *s, Queue *q1, Queue *q2);
int main()
{
    FILE *inFile = openFile("input.txt", "r");
    FILE *outFile = openFile("output.txt", "w");
    char instr[2][10] = {"", ""};
    Stack *Plate = new_Stack();
    Queue *LineA = new_Queue();
    Queue *LineB = new_Queue();
    while (!feof(inFile))
    {
        fscanf(inFile, "%s", instr[0]);   // Read instruction
        if (strcmp("POP", instr[0]) != 0) // POP do nothing
        {
            fscanf(inFile, "%s\n", instr[1]);
            if (instr[0][0] == 'P') // PUSH
            {
                push(Plate, atoi(instr[1]));
            }
            else if (instr[0][0] == 'E') // ENQUEUE
            {
                if (instr[1][0] == 'A')
                    enqueue(LineA, pop(Plate));
                else
                    enqueue(LineB, pop(Plate));
            }
            else if (instr[0][0] == 'D') // DEQUEUE
            {
                if (instr[1][0] == 'A')
                    fprintf(stdout, "%d\n", dequeue(LineA));
                else
                    fprintf(stdout, "%d\n", dequeue(LineB));
            }
            else
            {
                fprintf(stderr, "Wrong instruction!\n");
                exit(EXIT_FAILURE);
            }
#ifdef DEBUG
            printf("%s %s\n", instr[0], instr[1]);
            printALL(Plate, LineA, LineB);
            getchar();
#endif
        }
    }
    fclose(inFile);
    fclose(outFile);
    free(Plate);
    free(LineA);
    free(LineB);
    return 0;
}

FILE *openFile(const char *fileName, const char *mode)
{
    FILE *fp = fopen(fileName, mode);
    if (fp == NULL)
    {
        fprintf(stderr, "Error while opening \"%s\".\n", fileName);
        exit(EXIT_FAILURE);
    }
    return fp;
}

void printALL(Stack *s, Queue *qA, Queue *qB)
{
    printf("S: ");
    printS(s);
    printf("A: ");
    printQ(qA);
    printf("B: ");
    printQ(qB);
}