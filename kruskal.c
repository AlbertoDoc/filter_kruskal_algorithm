#include<stdlib.h>
#include<stdio.h>

typedef struct EDGE
{
    int u;
    int v;
    int weight;
} Edge;


int main() {
    int n, m;  // number of vertex and edges in graph
    int u, v, weight; // vertex u and v, weight of edge
    Edge *edge;

    printf("Insira a quantidade de vertices do grafo: ");
    scanf("%d", &n);

    printf("Insira a quantidade de arestas do grafo: ");
    scanf("%d", &m);

    int vertices[n];

    edge = (Edge*) malloc(m * sizeof(Edge));

    // giving for each vertex a identification
    for (int i = 1; i < n + 1; i++) {
        vertices[i] = i;
    }

    for (int i = 0; i < m; i++) {
        printf("\nInsira uma aresta na forma u, v, weight");
        scanf("%d %d %d", &u, &v, &weight);

        edge[i].u = u;
        edge[i].v = v;
        edge[i].weight = weight;
    }
}