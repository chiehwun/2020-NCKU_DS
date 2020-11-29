#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Double_LL.h"

#define max(a, b) (((a) > (b)) ? (a) : (b))

Node_tr *create_node_tr(char name[21], char phone[11])
{
    Node_tr *np = (Node_tr *)calloc(1, sizeof(Node_tr));
    if (!np) // p == NULL
    {
        fprintf(stderr, "create_node_tr(): Out of memory!\n");
        exit(EXIT_FAILURE);
    }
    np->left = np->right = NULL;
    np->height = np->bf = 0;
    strcpy(np->name, name);
    strcpy(np->phone, phone);
    return np;
}

Node_tr *search(Node_tr *root, char name[21])
{
    if (!root)
        return NULL;
    if (strcmp(name, root->name) < 0)
        return search(root->left, name);
    else if (strcmp(name, root->name) > 0)
        return search(root->right, name);
    else
        return root;
}

// update height, bf
void update(Node_tr *node)
{
    int left_height = !node->left ? -1 : node->left->height;
    int right_height = !node->right ? -1 : node->right->height;

    // Subtree max height + 1
    node->height = 1 + max(left_height, right_height);

    // Update balance factor
    node->bf = left_height - right_height;
    // fprintf(stderr, "(%d,%d)", node->height, node->bf);
}

Node_tr *L_rot(Node_tr *root)
{
    Node_tr *new_root = root->right;
    root->right = new_root->left;
    new_root->left = root;
    update(root);
    update(new_root);
    return new_root;
}

Node_tr *R_rot(Node_tr *root)
{
    Node_tr *new_root = root->left;
    root->left = new_root->right;
    new_root->right = root;
    update(root);
    update(new_root);
    return new_root;
}

Node_tr *LR_rot(Node_tr *root)
{
    root->left = L_rot(root->left);
    return R_rot(root);
}

Node_tr *RL_rot(Node_tr *root)
{
    root->right = R_rot(root->right);
    return L_rot(root);
}

Node_tr *balance(Node_tr *root)
{
    if (root->bf == 2)
    {
        if (root->left->bf < 0)
        {
            // LR case
#ifdef DEBUG
            fprintf(stderr, "->LR case");
#endif
            return LR_rot(root);
        }
        else
        {
            // LL case
#ifdef DEBUG
            fprintf(stderr, "->LL case");
#endif
            return R_rot(root);
        }
    }
    else if (root->bf == -2)
    {
        if (root->right->bf > 0)
        {
            // RL case
#ifdef DEBUG
            fprintf(stderr, "->RL case");
#endif
            return RL_rot(root);
        }
        else
        {
            // RR case
#ifdef DEBUG
            fprintf(stderr, "->RR case");
#endif
            return L_rot(root);
        }
    }
    return root;
}

Node_tr *insert_tree(Node_tr *root, char name[21], char phone[11])
{
    if (!root)
        return create_node_tr(name, phone);
    if (strcmp(name, root->name) < 0)
        root->left = insert_tree(root->left, name, phone);
    else
        root->right = insert_tree(root->right, name, phone);
    update(root);
    return balance(root);
}

void free_tree(Node_tr *root)
{
    if (!root)
        return;
    if (root->left)
        free_tree(root->left);
    if (root->right)
        free_tree(root->right);
#ifdef DEBUG
    fprintf(stderr, "free: %s\n", root->name);
#endif
    free(root);
}

// VRL pre-order traverse
void print_tree_PRE(FILE *fp, Node_tr *root, int first)
{
    if (!root)
        return;
    // Visit
    fprintf(fp, "%s%s", first == 0 ? "" : " ", root->name);
    if (root->left)
        print_tree_PRE(fp, root->left, 1);
    if (root->right)
        print_tree_PRE(fp, root->right, 1);
}

void visualize_tree(FILE *fp, Node_tr *root, int d)
{
    if (!root)
    {
        fprintf(stderr, "print_tree(): root is empty!\n");
        return;
    }
    LinkList *queue = create_ll();
    Node_tr *curr = root, *null_tr = create_node_tr("", "");
    int H = root->height;
    fprintf(fp, "H = %d\n", H);
    int line = 0, count = 0, gap;
    while (1)
    {
        if (count == (int)(pow(2, line) - 1))
            gap = (int)((pow(2, H - line - 1) - 0.5) * d);
        else
            gap = (int)((pow(2, H - line) - 1) * d);

        // Visualize part
        if (!curr || curr == null_tr)
            fprintf(fp, "%*s%*s", gap, "", d, "");
        else
            fprintf(fp, "%*s%*s", gap, "", d, curr->name);
        // Level Order algorithm
        if (line < H)
        {
            if (!curr || curr == null_tr)
            {
                push_node(queue, create_node(null_tr));
                push_node(queue, create_node(null_tr));
            }
            else
            {
                push_node(queue, create_node(curr->left));
                push_node(queue, create_node(curr->right));
            }
        }
        // Increment
        ++count;
        if ((int)(pow(2, line + 1) - 1) == count)
        {
            fprintf(fp, "\n");
            ++line;
        }

        if (!queue->head) // queue is empty
        {
            fprintf(fp, "\n\n");
            free(queue);
            return;
        }
        curr = pop_front_node(queue);
    }
}
#endif // BINARY_TREE_H