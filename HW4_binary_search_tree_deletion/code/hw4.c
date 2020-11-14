#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Binary_Tree.h"
void gen(int data_num);
int main()
{
    int input, i = 0;
    Node_tr *root;
    // Read the first line
    do
    {
        scanf("%d", &input);
        if (i == 0)
            root = create_node_tr(input);
        else
            append_search_tree(root, input);
        ++i;
    } while (getc(stdin) == ' ');
    // Read the second line
    do
    {
        scanf("%d", &input);
        root = delete_node_tr(root, input);
    } while (getc(stdin) == ' ');
    print_tree(root);
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

void gen(int data_num)
{
    srand(time(0));
    FILE *outFile = openFile("input.txt", "w");
    int arr[100], arr_out[100];

    for (int i = 0; i < 100; ++i)
        arr_out[i] = arr[i] = i;

    for (int i = 0; i < 100; ++i)
    {
        int a = rand() % 100;
        int b = rand() % 100;
        int temp = arr[a];
        arr[a] = arr[b];
        arr[b] = temp;
        int c = rand() % 100;
        int d = rand() % 100;
        temp = arr_out[c];
        arr_out[c] = arr_out[d];
        arr_out[d] = temp;
    }
    char c[2] = "";
    for (int i = 0; i < 100; ++i)
    {
        fprintf(outFile, "%s%d", c, arr[i]);
        c[0] = ' ';
    }
    c[0] = '\n';
    for (int i = 0; i < 100; ++i)
    {
        fprintf(outFile, "%s%d", c, arr_out[i]);
        c[0] = ' ';
    }

    fclose(outFile);
}
