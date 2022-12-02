#include<stdlib.h>
#include<stdio.h>

typedef struct EDGE
{
    int u;
    int v;
    int weight;
} Edge;

void printMST(Edge *T, int n) {
	int cost = 0;

	printf("Arestas selecionadas para compor a MST:\nu  v  w\n");
	for (int i = 0; i < n; i++) {
		printf("%d  %d  %d\n", T[i].u, T[i].v, T[i].weight);
		cost += T[i].weight;
	}

	printf("\nCusto = %d", cost);
}

void swap(Edge *x, Edge *y) {
	Edge temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

int partition(Edge *edges, int begin, int end){
	
    int p = begin, pivot=edges[end].weight;
	
    for (int i = begin; i < end; i++) {
		if (edges[i].weight <= pivot) {
			swap(&edges[i], &edges[p]);
			p++;
		}
	}

	swap(&edges[end], &edges[p]);

	return p;
}

void quickSort(Edge *edges, int begin, int end) {
	int q;

	if (begin >= end) {
		return;
    }

	q = partition(edges, begin, end);
	
    quickSort(edges, begin, q-1);
	quickSort(edges, q + 1, end);
}

void kruskal(Edge *edges, int* vertex, int n, int m) {
    Edge* tree;
    tree = (Edge*) malloc((n-1) * sizeof(Edge)); // by definition a tree must have n-1 edges

    quickSort(edges, 0, m-1); // Sorting edges by weight

    //printMST(edges, m); // only for testing if quicksort is working
}

int main() {
    int n, m;  // number of vertex and edges in graph
    int u, v, weight; // vertex u and v, weight of edge
    Edge *edges;

    printf("Insira a quantidade de vertices do grafo: ");
    scanf("%d", &n);

    printf("Insira a quantidade de arestas do grafo: ");
    scanf("%d", &m);

    int* vertex = (int*) malloc(n * sizeof(int));
    edges = (Edge*) malloc(m * sizeof(Edge));

    // giving for each vertex a identification
    for (int i = 1; i < n + 1; i++) {
        vertex[i] = i;
    }

    for (int i = 0; i < m; i++) {
        printf("\nInsira uma aresta na forma u, v, peso:\n");
        scanf("%d %d %d", &u, &v, &weight);

        edges[i].u = u;
        edges[i].v = v;
        edges[i].weight = weight;
    }

    kruskal(edges, vertex, n, m);
}