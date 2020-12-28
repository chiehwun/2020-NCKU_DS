#ifndef GRAPH_H
#define GRAPH_H
#include <stdio.h>
#include <stdlib.h>
#include "Double_LL.h"
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
// v_num: vertex number
graph *create_aoe(int v_num)
{
    graph *g = (graph *)calloc(1, sizeof(graph));
    if (!g)
    {
        fprintf(stderr, "create_aoe(): memory fail!");
        exit(EXIT_FAILURE);
    }
    g->vhead = (vheadnode *)calloc(v_num, sizeof(vheadnode));
    g->v_num = v_num;
    return g;
}

gnode *create_gnode(int v_end, int weight, int edge_code)
{
    gnode *n = (gnode *)calloc(1, sizeof(gnode));
    if (!n)
    {
        fprintf(stderr, "create_gnode(): memory fail!");
        exit(EXIT_FAILURE);
    }
    n->vertex = v_end;
    n->weight = weight;
    n->edge_code = edge_code;
    n->link = NULL;
    return n;
}

// Find start vertex: count == 0
int find_vstart(graph *g)
{
    if (!g)
    {
        fprintf(stderr, "find_vstart(): empty graph!");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < g->v_num; ++i)
        // valid vhead
        if (g->vhead[i].count == 0 && g->vhead[i].link)
            return i;
    fprintf(stderr, "find_vstart(): Cannot find!\n");
    exit(EXIT_FAILURE);
    return -1;
}

// g_in[0]: e_code
// g_in[1]: v_start
// g_in[2]: v_end
// g_in[3]: weight
graph *construct_aoe(int **g_in, int e_num)
{
    graph *g = create_aoe(100); // 0 <= vertex_code < 100
    for (int i = 0; i < e_num; ++i)
    {
        gnode *nd = g->vhead[g_in[1][i]].link;
        if (nd)
        {
            // Traverse to last gnode
            while (nd->link)
                nd = nd->link;
            nd->link = create_gnode(g_in[2][i], g_in[3][i], g_in[0][i]);
        }
        else
        {
            g->vhead[g_in[1][i]].link = create_gnode(g_in[2][i], g_in[3][i], g_in[0][i]);
        }
        ++g->vhead[g_in[2][i]].count; // when v_end occurs, do increment
    }
    g->v_start = find_vstart(g);
    return g;
}

// g_in[0]: e_code
// g_in[1]: v_start
// g_in[2]: v_end
// g_in[3]: weight
graph *construct_aoe_inv(int **g_in, int e_num)
{
    graph *g = create_aoe(100); // 0 <= vertex < 100
    for (int i = 0; i < e_num; ++i)
    {
        gnode *nd = g->vhead[g_in[2][i]].link;
        if (nd)
        {
            // Traverse to last gnode
            while (nd->link)
                nd = nd->link;
            nd->link = create_gnode(g_in[1][i], g_in[3][i], g_in[0][i]);
        }
        else
        {
            g->vhead[g_in[2][i]].link = create_gnode(g_in[1][i], g_in[3][i], g_in[0][i]);
        }
        ++g->vhead[g_in[1][i]].count; // when v_start occurs, do increment
    }
    g->v_start = find_vstart(g);
    return g;
}
// mode: (0, early-vertex) (1, late-vertex)
void cal_vert_rec(int vertex_rec[][100], graph *g, int mode)
{
    LinkList *stack = create_ll();
    push_front(stack, create_node(g->vhead + g->v_start));
    vertex_rec[0][g->v_start] = 1; // set to valid
    while (!LL_empty(stack))
    {
        vheadnode *vhd = pop_front(stack);
        gnode *gnd = vhd->link;
        while (gnd)
        {
            // fprintf(stderr, "v[%d] = v[%d] + %d\n",
            //         gnd->vertex,
            //         vhd - g->vhead,
            //         gnd->weight);
            vertex_rec[0][gnd->vertex] = 1; // set to valid
            if (mode == 0)
                vertex_rec[1][gnd->vertex] = MAX(vertex_rec[1][gnd->vertex],
                                                 vertex_rec[1][vhd - g->vhead] + gnd->weight);
            else
                vertex_rec[2][gnd->vertex] = MIN(vertex_rec[2][gnd->vertex],
                                                 vertex_rec[2][vhd - g->vhead] - gnd->weight);

            if (g->vhead[gnd->vertex].count == 1)
                push_front(stack,
                           create_node(g->vhead + gnd->vertex));
            else
                --g->vhead[gnd->vertex].count;
            gnd = gnd->link;
        }
        // fprintf(stderr, "\n");
    }
    free_LL(stack);
}

// mode: (0, early-edge) (1, late-edge)
void cal_edge_rec(int *edge_rec, int vertex_rec[100], graph *g, int mode)
{
    LinkList *queue = create_ll();
    // start from vhead + start (<-- vheadnode*)
    push_back(queue, create_node(g->vhead + g->v_start));
    while (!LL_empty(queue))
    {
        vheadnode *vhd = pop_front(queue);
        for (gnode *gnd = vhd->link; gnd; gnd = gnd->link)
        {
            push_back(queue,
                      create_node(g->vhead + gnd->vertex));
            if (mode == 0)
                edge_rec[gnd->edge_code] = vertex_rec[vhd - g->vhead];
            else
                edge_rec[gnd->edge_code] = vertex_rec[vhd - g->vhead] - gnd->weight;
        }
    }
    free_LL(queue);
}

void print_graph(graph *g)
{
    if (!g)
    {
        fprintf(stderr, "print_graph(): empty graph!\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < g->v_num; ++i)
    {
        if (g->vhead[i].count > 0 || g->vhead[i].link)
        {
            fprintf(stderr, "v_%-3d: %-3d", i, g->vhead[i].count);
            gnode *nd = g->vhead[i].link;
            while (nd)
            {
                fprintf(stderr, " --> v_%-3d, a_%-3d, %-3d", nd->vertex, nd->edge_code, nd->weight);
                nd = nd->link;
            }
            fprintf(stderr, "\n");
        }
    }
}

#endif // GRAPH_H