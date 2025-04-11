#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} NODE;

typedef struct Graph {
    int vertices;
    int *visited;
    NODE **adjacency_lists;
} GPH;

// Utilitare
NODE *create_node(int v) {
    NODE *new_node = malloc(sizeof(NODE));
    new_node->data = v;
    new_node->next = NULL;
    return new_node;
}

GPH *create_graph(int vertices) {
    GPH *graph = malloc(sizeof(GPH));
    graph->vertices = vertices;
    graph->adjacency_lists = malloc(vertices * sizeof(NODE *));
    graph->visited = malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adjacency_lists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

void add_edge(GPH *graph, int src, int dest) {
    NODE *new_node = create_node(dest);
    new_node->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = new_node;

    // Pentru graf neorientat
    new_node = create_node(src);
    new_node->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = new_node;
}

void insert_edges(int nr_of_edges, GPH *graph) {
    int src, dest;
    printf("Adauga %d muchii (nodurile numerotate de la 0 la %d):\n", nr_of_edges, graph->vertices - 1);
    for (int i = 0; i < nr_of_edges; i++) {
        printf("Muchia %d: ", i + 1);
        scanf("%d%d", &src, &dest);
        add_edge(graph, src, dest);
    }
}

// BFS utilitare (folosim lista simplă ca o coadă)
void enqueue(NODE **queue, int data) {
    NODE *new_node = create_node(data);
    if (*queue == NULL) {
        *queue = new_node;
    } else {
        NODE *temp = *queue;
        while (temp->next)
            temp = temp->next;
        temp->next = new_node;
    }
}

int dequeue(NODE **queue) {
    if (*queue == NULL)
        return -1;
    int data = (*queue)->data;
    NODE *temp = *queue;
    *queue = (*queue)->next;
    free(temp);
    return data;
}

int is_empty(NODE *queue) {
    return queue == NULL;
}

// Parcurgeri
void DFS(GPH *graph, int vertex) {
    NODE *temp = graph->adjacency_lists[vertex];
    graph->visited[vertex] = 1;
    printf("%d ", vertex);

    while (temp != NULL) {
        int connected_vertex = temp->data;
        if (graph->visited[connected_vertex] == 0) {
            DFS(graph, connected_vertex);
        }
        temp = temp->next;
    }
}

void BFS(GPH *graph, int start_vertex) {
    NODE *queue = NULL;
    graph->visited[start_vertex] = 1;
    enqueue(&queue, start_vertex);

    while (!is_empty(queue)) {
        int current_vertex = dequeue(&queue);
        printf("%d ", current_vertex);

        NODE *temp = graph->adjacency_lists[current_vertex];
        while (temp) {
            int adj_vertex = temp->data;
            if (graph->visited[adj_vertex] == 0) {
                graph->visited[adj_vertex] = 1;
                enqueue(&queue, adj_vertex);
            }
            temp = temp->next;
        }
    }
}

void wipe_visited(GPH *graph) {
    for (int i = 0; i < graph->vertices; i++) {
        graph->visited[i] = 0;
    }
}

void print_graph(GPH *graph) {
    printf("Reprezentarea grafului:\n");
    for (int i = 0; i < graph->vertices; i++) {
        NODE *temp = graph->adjacency_lists[i];
        printf("%d: ", i);
        while (temp) {
            printf("%d -> ", temp->data);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

// Main
int main() {
    int nr_of_vertices, nr_of_edges, start_vertex;

    printf("Cate noduri are graful? ");
    scanf("%d", &nr_of_vertices);
    printf("Cate muchii are graful? ");
    scanf("%d", &nr_of_edges);

    GPH *graph = create_graph(nr_of_vertices);
    insert_edges(nr_of_edges, graph);

    print_graph(graph);

    printf("De unde plecam in DFS? ");
    scanf("%d", &start_vertex);
    printf("Parcurgere cu DFS: ");
    DFS(graph, start_vertex);
    printf("\n");

    wipe_visited(graph);

    printf("De unde plecam in BFS? ");
    scanf("%d", &start_vertex);
    printf("Parcurgere cu BFS: ");
    BFS(graph, start_vertex);
    printf("\n");

    return 0;
}

