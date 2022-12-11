#include<stdlib.h>
#include<stdio.h>
#include<time.h>


typedef struct EDGE
{
    int u;
    int v;
    int weight;
} Edge;

void printMST(Edge *T, int n) {
    int cost = 0;

    printf("\nArestas selecionadas para compor a MST:\nu  v  w\n");
    for (int i = 0; i < n; i++) {
    	printf("%d  %d  %d\n", T[i].u, T[i].v, T[i].weight);
    	cost += T[i].weight;
    }

    printf("\nCusto = %d\n", cost);
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

int find(int u, int n, int parent[]) {
	int i = 0, A[n];
	
    while(u != parent[u]) {
		A[i] = u;
		u = parent[u];
		i++;
	}

	i--;
	
    while(i >= 0) {
		parent[A[i]] = u;
		i--;
	}

	return u;
}

void unionByRank(int u, int v, int n, int parent[], int rank[]) {
	int x, y;
	x = find(u, n, parent);
	y = find(v, n, parent);
	
    if (rank[x] < rank[y]) {
		parent[x] = y;        
    } else if (rank[y] < rank[x]) {
		parent[y] = x;
    } else {
		parent[x] = y;
		rank[y]++;
	}
}

void kruskal(Edge *edges, int n, int m, int parent[], int rank[]) {
    Edge* tree;
    tree = (Edge*) malloc((n-1) * sizeof(Edge)); // by definition a tree must have n-1 edges

    quickSort(edges, 0, m-1); // Sorting edges by weight

    //printMST(edges, m); // only for testing if quicksort is working

    int includedVertexCount = 0, x, y;
    for (int i = 0; i < m; i++) {
        Edge edge = edges[i];

        if (includedVertexCount == n - 1) {
            // The tree is already with the maximum edges
            break;
        }
        
        // The find method uses the absolute root to determine whether two vertices belong to the same set.
        x = find(edge.u, n, parent);
        y = find(edge.v, n, parent);

        // We compare the two absolut root's to determine if they are in the same set
        // if x != y is true so, edge.u and edge.v is not in the same set
        if (x != y) {
            tree[includedVertexCount] = edge;

            // Using unionByRank to make the union of two vertex
            unionByRank(x, y, n, parent, rank);
            includedVertexCount++;
        }
    }

    printMST(tree, n - 1);
}

int main() {
    int n, m;  // number of vertex and edges in graph
    int u, v, weight; // vertex u and v, weight of edge
    Edge *edges;

    printf("Insira a quantidade de vertices do grafo: ");
    scanf("%d", &n);

    printf("Insira a quantidade de arestas do grafo: ");
    scanf("%d", &m);

    int parent[n + 1], rank[n + 1];

    int* vertex = (int*) malloc(n * sizeof(int));
    edges = (Edge*) malloc(m * sizeof(Edge));

    // giving for each vertex a identification
    for (int i = 1; i < n + 1; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    for (int i = 0; i < m; i++) {
        printf("\nInsira uma aresta na forma u, v, peso:\n");
        scanf("%d %d %d", &u, &v, &weight);

        edges[i].u = u;
        edges[i].v = v;
        edges[i].weight = weight;
    }
    clock_t start, end;
    start = clock();
    kruskal(edges, n, m, parent, rank);
    end = clock();
    double duration = ((double)end - start)/CLOCKS_PER_SEC;

    printf("Tempo de execucao do algoritmo em segundos: %f\n", duration);
}