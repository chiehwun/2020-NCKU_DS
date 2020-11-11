#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Double_LL.h"

Node_tr *create_node_tr(int key)
{
    Node_tr *np = (Node_tr *)calloc(1, sizeof(Node_tr));
    if (!np) // p == NULL
    {
        fprintf(stderr, "create_node_tr(): Out of memory!\n");
        exit(EXIT_FAILURE);
    }
    np->key = key;
     np->left = np->right = NULL;
    return np;
}

void append_search_tree(Node_tr *root, int val)
{
    if (!root)
    {
        fprintf(stderr, "build_search_tree(): root is empty!\n");
        exit(EXIT_FAILURE);
    }
    Node_tr *curr = root;
    Node_tr *new_node = create_node_tr(val);
    while (1)
    {
        if (val < curr->key) // no repeated key value
        {
            if (curr->left)
                curr = curr->left; // Move to next non-NULL node
            else
            {
                curr->left = new_node;
                break;
            }
        }
        else
        {
            if (curr->right)
                curr = curr->right; // Move to next non-NULL node
            else
            {
                curr->right = new_node;
                break;
            }
        }
    }
}

Node_tr *findMin(Node_tr *root)
{
    while (root && root->left)
        root = root->left;
    return root;
}

Node_tr *delete_node_tr(Node_tr *root, int val)
{
    if (!root)  // root is empty
        return root;
    else if (val < root->key)
        root->left = delete_node_tr(root->left, val);   // return left node pointer or one of its child
    else if (val > root->key)
        root->right = delete_node_tr(root->right, val); // return right node pointer or one of its child
    else
    {
        // Case 1: No child
        if (!root->left && !root->right)
        {
            free(root);
            root = NULL;
        }
        // Case 2: 1 child
        else if (!root->left)
        {
            Node_tr *temp = root;
            root = root->right; // return right node to update the pointer from previous call
            free(temp);
        }
        else if (!root->right)
        {
            Node_tr *temp = root;
            root = root->left;  // return left node to update the pointer from previous call
            free(temp);
        }
        // Case 3: 2 children
        else
        {
            Node_tr *temp = findMin(root->right);
            root->key = temp->key; // replace with the minimum key
            root->right = delete_node_tr(root->right, temp->key);
        }
    }
    return root;
}


void print_tree(Node_tr *root) // Level Order
{
    if (!root)
    {
        fprintf(stderr, "print_tree(): root is empty!\n");
        return;
    }
    LinkList *queue = create_ll();
    Node_tr *curr = root;
    char c[2] = "";
    while (curr)
    {
        printf("%s%d", c, curr->key);
        c[0] = '\n';
        if (curr->left)
            push_node(queue, create_node(curr->left));
        if (curr->right)
            push_node(queue, create_node(curr->right));
        if (!queue->head) // queue is empty
        {
            free(queue);
            return;
        }
        curr = pop_front_node(queue);
    }
    free(queue);
}
#endif // BINARY_TREE_H

// void delete_node_tr_old(Node_tr **root, int val)
// {
//     if (!root)
//     {
//         fprintf(stderr, "delete_node_tr(): root is empty!\n");
//         return;
//     }
//     /* Step 1. Find the key Node_tr */
//     Node_tr *next = *root;
//     Node_tr *res = *root;
//     int prt_isleft = 1;
//     while (next)
//     {
//         res = next;
//         if (val == res->key)
//             break; // key found
//         else if (val < res->key)
//         {
//             next = res->left;
//             prt_isleft = 1;
//         }
//         else
//         {
//             next = res->right;
//             prt_isleft = 0;
//         }
//     }
//     if (!next) // key not found
//     {
//         fprintf(stderr, "delete_node_tr(): %d not found.\n", val);
//         return;
//     }
//     /* Step 2. Delete the node_tr */
//     fprintf(stderr, "delete_node_tr(): found delete node_tr: %d.\n", val);
//     // Case 1: leaf node
//     if (!res->left && !res->right)
//     {
//         fprintf(stderr, "delete_node_tr(): Case 1: leaf node\n");
//         if (prt_isleft)
//             res->prt->left = NULL;
//         else
//             res->prt->right = NULL;
//     }
//     else
//     {
//         Node_tr *swp;
//         if (!res->right)
//         {
//             // Case 2: no right child >> shift res->left
//             fprintf(stderr, "delete_node_tr(): Case 2: no right child\n");
//             swp = res->left;
//             swp->prt = res->prt;

//             if (res->prt)
//             {
//                 // is not root
//                 fprintf(stderr, "delete_node_tr(): is not root\n");
//                 res->prt->right = swp;
//             }
//             else
//             {
//                 // is root
//                 fprintf(stderr, "delete_node_tr(): is root\n");
//                 // change root
//                 *root = swp;
//             }


//         }
//         else
//         {
//             // Case 3: right child exists
//             fprintf(stderr, "delete_node_tr(): Case 3: right child exists\n");
//             swp = res->right;
//             fprintf(stderr, "res: %d, val: %d \n", res->key, val);
//             if (!swp->left)
//             {
//                 // right child has no left child >> shift res->right
//                 fprintf(stderr, "delete_node_tr(): right child has no left child\n");
//                 swp->prt = res->prt;
//                 if (res->prt)
//                 {
//                     // is not root
//                     fprintf(stderr, "delete_node_tr(): is not root\n");
//                     res->prt->right = swp;
//                 }
//                 else
//                 {
//                     // is root
//                     fprintf(stderr, "delete_node_tr(): is root\n");
//                     swp->prt = NULL;
//                     swp->left = res->left;
//                     res->left->prt = swp;
//                     // change root
//                     *root = swp;
//                 }
//             }
//             else
//             {
//                 // Find the smallest node in right subtree
//                 do
//                 {
//                     next = swp->left;
//                     if (next)
//                         swp = next;
//                 } while (next);
//                 swp->prt->left = NULL;
//                 swp->left = res->left;
//                 swp->right = res->right;
//                 swp->prt = res->prt;
//             }
//         }
//     }
//     free(res);
// }

