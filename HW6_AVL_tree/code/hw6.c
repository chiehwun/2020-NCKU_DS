#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AVL_Tree.h"
// #define DEBUG
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

int main()
{
    FILE *infile_src = stdin;
    FILE *outfile_src = stdout;
    Node_tr *root = NULL;
    char name[21] = "";
    char phone[11] = "";
    char instr[2] = "";
    // Construct AVL tree
    while (1)
    {
        // fetch instruction
        fscanf(infile_src, "%s", name);
        // E: program terminate
        if (strcmp("E", name) == 0)
        {
            free_tree(root);
            break;
        }
        // judge instruction
        if (strcmp("D", name) == 0 || strcmp("S", name) == 0)
        {
            if (instr[0] == 'D')
            {
                // visualize_tree(stderr, root, 9);
                print_tree_PRE(outfile_src, root, 0); // end of D
            }
            // update instruction
            strcpy(instr, name);
            // D & S: Read name at first
            fscanf(infile_src, "%s", name);
        }
        // D: construct AVL tree
        if (instr[0] == 'D')
        {
            fscanf(infile_src, "%s\n", phone);
            root = insert_tree(root, name, phone);
#ifdef DEBUG
            fprintf(stderr, "insert: \"%s\", ", name);
            visualize_tree(stderr, root, 9);
#endif
        }
        // S: search AVL tree
        else if (instr[0] == 'S')
        {
            // Search in AVL tree
            Node_tr *res = search(root, name);
            if (res) // Node exists
                fprintf(outfile_src, "\n%s %s", res->name, res->phone);
            else
                fprintf(outfile_src, "\n%s null", name);
        }
    }
    return 0;
}