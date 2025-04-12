#include <stdio.h>
#include <stdlib.h>
//Calapod Stefan Vinci 313AC
typedef struct Node {
    int data;
    struct Node *next;
} NODE;

typedef struct Graph {
    int v;
    NODE **adj;
} GPH;

GPH *create_graph(int v) {
    GPH *g = malloc(sizeof(GPH));
    g->v = v;
    g->adj = malloc(sizeof(NODE *) * v);
    for (int i = 0; i < v; i++) {
        g->adj[i] = NULL;
    }
    return g;
}

NODE *create_node(int v) {
    NODE *new_node = malloc(sizeof(NODE));
    new_node->data = v;
    new_node->next = NULL;
    return new_node;
}

void add_edge(GPH *g, int src, int dest) {
    NODE *n = create_node(dest);
    n->next = g->adj[src];
    g->adj[src] = n;

    n = create_node(src);
    n->next = g->adj[dest];
    g->adj[dest] = n;
}

int has_direct_path(GPH *g, int src, int dest) {
    NODE *temp = g->adj[src];
    while (temp != NULL) {
        if (temp->data == dest)
            return 1;
        temp = temp->next;
    }
    return 0;
}
//test
int main() {
    int nrv, edg_nr;
    printf("Cate restaurante (noduri)? ");
    scanf("%d", &nrv);

    printf("Cate drumuri directe (muchii)? ");
    scanf("%d", &edg_nr);

    GPH *g = create_graph(nrv);

    printf("Introdu %d perechi (nod1 nod2):\n", edg_nr);
    for (int i = 0; i < edg_nr; i++) {
        int src, dest;
        scanf("%d %d", &src, &dest);
        add_edge(g, src, dest);
    }

    int a, b;
    printf("Verificare drum direct intre care doua restaurante (noduri)?\n");
    scanf("%d %d", &a, &b);

    if (has_direct_path(g, a, b))
        printf("Exista drum direct intre %d si %d.\n", a, b);
    else
        printf("NU exista drum direct intre %d si %d.\n", a, b);

    return 0;
}
