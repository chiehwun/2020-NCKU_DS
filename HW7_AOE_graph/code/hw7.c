#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "graph.h"

int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int main(int argc, char *argv[])
{
    // Read from stdin
    int temp;
    scanf("%d", &temp);
    const int E_NUM = temp;
    fprintf(stderr, "egde_num: %d\n", E_NUM);
    int **GIN = (int **)malloc(4 * sizeof(int *));
    for (int i = 0; i < 4; ++i)
        GIN[i] = (int *)calloc(E_NUM, sizeof(int));
    for (int i = 0; i < E_NUM; ++i)
        scanf("%d %d %d %d",
              GIN[0] + i,  //e_code
              GIN[1] + i,  // v_start
              GIN[2] + i,  // v_end
              GIN[3] + i); // weight

    // Construct AOE graph by input file
    graph *g = construct_aoe(GIN, E_NUM);
    graph *g_inv = construct_aoe_inv(GIN, E_NUM);
    fprintf(stderr, "Normal: \n");
    print_graph(g);
    fprintf(stderr, "\nInvert: \n");
    print_graph(g_inv);

    // vertex_rec[0]: valid bit
    // vertex_rec[1]: early
    // vertex_rec[2]: late
    int vertex_rec[3][100] = {0};
    // Calculate early vertex
    fprintf(stderr, "Calculate early: g->v_start = %d\n", g->v_start);
    cal_vert_rec(vertex_rec, g, 0);

    // Find latest length
    int latest = -1;
    for (int i = 0; i < g->v_num; ++i)
        if (vertex_rec[0][i])
            latest = MAX(latest, vertex_rec[1][i]);
    // initialize vertex_rec[2]
    for (int i = 0; i < g->v_num; ++i)
        if (vertex_rec[0][i])
            vertex_rec[2][i] = latest;

    // Calculate late vertex
    fprintf(stderr, "Calculate late: g_inv->v_start = %d\n", g_inv->v_start);
    cal_vert_rec(vertex_rec, g_inv, 1);

    fprintf(stderr, "Vertex Record: [e] [l]\n");
    for (int i = 0; i < g->v_num; ++i)
        if (vertex_rec[0][i])
            fprintf(stderr, "v_%-9d: %3d %3d\n",
                    i, vertex_rec[1][i], vertex_rec[2][i]);
    /* Find the edges thru by breadth-first search */
    // edge_rec[0]: early
    // edge_rec[1]: late
    int **edge_rec = (int **)malloc(2 * sizeof(int *));
    for (int i = 0; i < 2; ++i)
        edge_rec[i] = (int *)calloc(E_NUM, sizeof(int));
    // Initialize all edge_rec[1]
    for (int i = 0; i < E_NUM; ++i)
        edge_rec[1][i] = latest;

    // Calculate early edge
    cal_edge_rec(edge_rec[0], vertex_rec[1], g, 0);
    // Calculate late edge
    cal_edge_rec(edge_rec[1], vertex_rec[2], g_inv, 1);

    fprintf(stderr, "Edge Record: (e) (l)\n");
    for (int i = 0; i < E_NUM; ++i)
    {
        printf("%d %d %d\n", i, edge_rec[0][i], edge_rec[1][i]);
        fprintf(stderr, "a_%-9d: %3d %3d\n", i, edge_rec[0][i], edge_rec[1][i]);
    }
    int crt_edg_num = 0;
    int *critical_edge = (int *)calloc(E_NUM, sizeof(int));
    for (int i = 0; i < E_NUM; ++i)
        // critical edge
        if (edge_rec[0][i] == edge_rec[1][i])
        {
            critical_edge[crt_edg_num] = i;
            ++crt_edg_num;
        }
    qsort(critical_edge, crt_edg_num, sizeof(*critical_edge), compare);
    fprintf(stderr, "Critical edges: #%d\n", crt_edg_num);
    for (int i = 0; i < crt_edg_num; ++i)
    {
        printf("%d%s", critical_edge[i], (i == crt_edg_num - 1 ? "" : " "));
        fprintf(stderr, "%d%s", critical_edge[i], (i == crt_edg_num - 1 ? "" : " "));
    }
    fprintf(stderr, "\n");
    return 0;
}