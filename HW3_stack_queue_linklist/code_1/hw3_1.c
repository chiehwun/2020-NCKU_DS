// #define DEBUG
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Double_LL.h"
FILE *openFile(const char *fileName, const char *mode);
void printALL(LinkList *s, LinkList *qA, LinkList *qB);
int main()
{
    // FILE *inFile = openFile("p1_input.txt", "r");
    FILE *inFile = stdin;
    char instr[2][10] = {"", ""};
    LinkList *plate = create_ll();
    LinkList *line_a = create_ll();
    LinkList *line_b = create_ll();
    while (!feof(inFile))
    {
        fscanf(inFile, "%s", instr[0]); // Read instruction
        if (strcmp("^Z", instr[0]) == 0)
            break;
        else if (strcmp("POP", instr[0]) != 0) // POP do nothing
        {
            fscanf(inFile, "%s\n", instr[1]);
            if (instr[0][0] == 'P') // PUSH
            {
                push_node(plate, create_node(atoi(instr[1])));
            }
            else if (instr[0][0] == 'E') // ENQUEUE
            {
                if (instr[1][0] == 'A')
                    push_front_node(line_a, create_node(pop_node(plate)));
                else
                    push_front_node(line_b, create_node(pop_node(plate)));
            }
            else if (instr[0][0] == 'D') // DEQUEUE
            {
                if (instr[1][0] == 'A')
                    fprintf(stdout, "%d\n", pop_node(line_a));
                else
                    fprintf(stdout, "%d\n", pop_node(line_b));
            }
            else
            {
                fprintf(stderr, "%s %s", instr[0], instr[1]);
                fprintf(stderr, "Wrong instruction!\n");
                exit(EXIT_FAILURE);
            }
#ifdef DEBUG
            printf("%s %s\n", instr[0], instr[1]);
            printALL(plate, line_a, line_b);
#endif
        }
    }
    // Deallocate heap
    free_LL(plate);
    free_LL(line_a);
    free_LL(line_b);
    free(plate);
    free(line_a);
    free(line_b);
    return 0;
}

FILE *openFile(const char *fileName, const char *mode)
{
    FILE *fp = fopen(fileName, mode);
    if (!fp)
    {
        fprintf(stderr, "Error while opening \"%s\".\n", fileName);
        exit(EXIT_FAILURE);
    }
    return fp;
}

void printALL(LinkList *s, LinkList *qA, LinkList *qB)
{
    printf("S: ");
    printLL(s, 0);
    printf("A: ");
    printLL(qA, 0);
    printf("B: ");
    printLL(qB, 0);
}